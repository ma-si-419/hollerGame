
SamplerState smp : register(s0);
Texture2D tex : register(t0);
Texture2D dissolveTex : register(t3);

float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);

// 頂点シェーダーの出力
struct PS_INPUT
{
    float4 Diffuse : COLOR0; // ディフューズカラー
    float4 Specular : COLOR1; // スペキュラカラー
    float3 Normal : NORMAL;
    float2 TexCoords0 : TEXCOORD0; // テクスチャ座標
    float4 svPosition : SV_POSITION; // 座標( プロジェクション空間 )
    float4 Position : POSITION0; // 座標( プロジェクション空間 )
    float4 P : POSITION1; // 座標( プロジェクション空間 )
};

struct PS_OUTPUT
{
    float4 color : SV_Target0;
};

cbuffer LightData : register(b4)
{
    //ポイントライトの位置
    float3 PLightPos;
    //パディング
    float pad1;
    //ポイントライトの色
    float3 PLightColor;
    //ポイントライトの影響力
    float PLightPower;
    //ディレクションライトの角度
    float3 DLightDir;
    //パディング
    float pad2;
    //ディレクションライトの色
    float3 DLightColor;
    //パディング
    float pad3;
    //スポットライトの位置   
    float3 SpLightPos;
    //パディング
    float pad4;
    //スポットライトの色
    float3 SpLightColor;
    //スポットライトの影響力
    float SpLightPower;
    //スポットライトの射出方向
    float3 SpLightDir;
    //スポットライトの射出角度
    float SpLightAngle;
    //視点の位置
    float3 CameraPos;
    //パディング
    float pad5;
};


PS_OUTPUT main(PS_INPUT input)
{
    float4 texCol = tex.Sample(smp, input.TexCoords0);
    
    /*ディレクションライト*/
    /////////////////////////////////////////////////////////////
    //ディレクションライトとピクセルの外積を求める
    
    //最終的に入れるディレクションライトの変数
    float3 DLight = float3(0, 0, 0);
    //ディレクションライトの計算
    {
        float DLightAngle = dot(input.Normal, DLightDir);
        DLightAngle *= -1;
        if (DLightAngle < 0.0f)
        {
            DLightAngle = 0;
        }
        DLight = DLightColor * DLightAngle;
    }
    /////////////////////////////////////////////////////////////
   
    /*ポイントライト*/
    /////////////////////////////////////////////////////////////
    //ピクセルに入る光の向きを求める
    
    //最終的に入れるポイントライトの変数
    float3 PLight = float3(0, 0, 0);
    
    //ポイントライトの計算
    {
        float3 PLightIncidentVec = input.Position.xyz - PLightPos;
        PLightIncidentVec = normalize(PLightIncidentVec);
    
        //ピクセルの法線とライトの方向の内積を計算する
        float temp = dot(input.Normal, PLightIncidentVec);
        temp *= -1;
        //内積の結果が0以下なら0にする
        if (temp < 0.0f)
        {
            temp = 0;
        }
    
        //拡散反射光を求める
        float3 diffuseLight = CalcLambertDiffuse(PLightIncidentVec, PLightColor, input.Normal);
        //鏡面反射光を求める
        float3 specularLight = CalcPhongSpecular(PLightIncidentVec, PLightColor, input.Position.xyz, input.Normal);
    
        //距離を求める
        float distance = length(input.Position.xyz - PLightPos);
        //影響力を計算する
        float power = 1.0f - 1.0f / PLightPower * distance;
        //影響力がマイナスになる場合0にする
        if (power < 0.0f)
        {
            power = 0;
   
        }
    
        //影響範囲を絞る
        power = pow(power, 3);
    
        
        //if (power >= 0.7f)
        //{
        //    power = 0.7f;
        //}
        
        specularLight *= power;
        diffuseLight *= power;
    
    
        PLight = float3(specularLight + diffuseLight);
    }
    
    ////////////////////////////////////////////////////////////////
   
    /*スポットライト*/
    ////////////////////////////////////////////////////////////////
    
    //最終的に入れるスポットライトの変数
    float3 SLight = float3(0, 0, 0);
    
    //スポットライトの計算
    {
        float3 SLightIncidentVec = input.Position.xyz - SpLightPos;
        
        SLightIncidentVec = normalize(SLightIncidentVec);
        
        float3 diffuseLight = CalcLambertDiffuse(SLightIncidentVec, SpLightColor, input.Normal);
        
        float3 specularLight = CalcPhongSpecular(SLightIncidentVec, SpLightColor, input.Position.xyz, input.Normal);

        float3 distance = length(input.Position.xyz - SpLightPos);
        
        float power = 1.0f - 1.0f / SpLightPower * distance;
        
        if (power < 0.0f)
        {
            power = 0.0f;
        }

        //距離減衰の絞り
        power = pow(power, 0.3f);
        
        diffuseLight *= power;
        specularLight *= power;

        
        
        float angle = dot(SLightIncidentVec, SpLightDir);
        
        angle = abs(acos(angle));

        power = 1.0f - 1.0f / SpLightAngle * angle;
        
        if (power < 0.0f)
        {
            power = 0.0f;
        }
        

        //光の方向による減衰の絞り
        power = pow(power, 0.9f);

        
        
        diffuseLight *= power;
        specularLight *= power;
        
        SLight = float3(specularLight + diffuseLight);

    }
    ////////////////////////////////////////////////////////////////
    
    float3 finalColor = texCol.rgb * (PLight + DLight + SLight);
    
    PS_OUTPUT outData;
    
    outData.color = float4(finalColor, 1);
    
    return outData;
}


/// <summary>
/// Lambert拡散反射光を計算する
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;

    t = (t + 1) * 0.5;
    
    // 内積の値を0以上の値にする
    t = max(0.0f, t);

    // 拡散反射光を計算する
    return lightColor * t;
}
/// <summary>
/// Phong鏡面反射光を計算する
/// </summary>
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // 反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);

    // 光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = CameraPos - worldPos;
    toEye = normalize(toEye);

    // 鏡面反射の強さを求める
    float t = dot(refVec, toEye);

    t = (t + 1) * 0.5;
    
    // 鏡面反射の強さを0以上の数値にする
    t = max(0.0f, t);

    // 鏡面反射の強さを絞る
    t = pow(t, 5.0f);

    // 鏡面反射光を求める
    return lightColor * t;
}
