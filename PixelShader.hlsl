
SamplerState smp : register(s0);
Texture2D tex : register(t0);
Texture2D dissolveTex : register(t3);

float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);

// ���_�V�F�[�_�[�̏o��
struct PS_INPUT
{
    float4 Diffuse : COLOR0; // �f�B�t���[�Y�J���[
    float4 Specular : COLOR1; // �X�y�L�����J���[
    float3 Normal : NORMAL;
    float2 TexCoords0 : TEXCOORD0; // �e�N�X�`�����W
    float4 svPosition : SV_POSITION; // ���W( �v���W�F�N�V������� )
    float4 Position : POSITION0; // ���W( �v���W�F�N�V������� )
    float4 P : POSITION1; // ���W( �v���W�F�N�V������� )
};

struct PS_OUTPUT
{
    float4 color : SV_Target0;
};

cbuffer LightData : register(b4)
{
    //�|�C���g���C�g�̈ʒu
    float3 PLightPos;
    //�p�f�B���O
    float pad1;
    //�|�C���g���C�g�̐F
    float3 PLightColor;
    //�|�C���g���C�g�̉e����
    float PLightPower;
    //�f�B���N�V�������C�g�̊p�x
    float3 DLightDir;
    //�p�f�B���O
    float pad2;
    //�f�B���N�V�������C�g�̐F
    float3 DLightColor;
    //�p�f�B���O
    float pad3;
    //�X�|�b�g���C�g�̈ʒu   
    float3 SpLightPos;
    //�p�f�B���O
    float pad4;
    //�X�|�b�g���C�g�̐F
    float3 SpLightColor;
    //�X�|�b�g���C�g�̉e����
    float SpLightPower;
    //�X�|�b�g���C�g�̎ˏo����
    float3 SpLightDir;
    //�X�|�b�g���C�g�̎ˏo�p�x
    float SpLightAngle;
    //���_�̈ʒu
    float3 CameraPos;
    //�p�f�B���O
    float pad5;
};


PS_OUTPUT main(PS_INPUT input)
{
    float4 texCol = tex.Sample(smp, input.TexCoords0);
    
    /*�f�B���N�V�������C�g*/
    /////////////////////////////////////////////////////////////
    //�f�B���N�V�������C�g�ƃs�N�Z���̊O�ς����߂�
    
    //�ŏI�I�ɓ����f�B���N�V�������C�g�̕ϐ�
    float3 DLight = float3(0, 0, 0);
    //�f�B���N�V�������C�g�̌v�Z
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
   
    /*�|�C���g���C�g*/
    /////////////////////////////////////////////////////////////
    //�s�N�Z���ɓ�����̌��������߂�
    
    //�ŏI�I�ɓ����|�C���g���C�g�̕ϐ�
    float3 PLight = float3(0, 0, 0);
    
    //�|�C���g���C�g�̌v�Z
    {
        float3 PLightIncidentVec = input.Position.xyz - PLightPos;
        PLightIncidentVec = normalize(PLightIncidentVec);
    
        //�s�N�Z���̖@���ƃ��C�g�̕����̓��ς��v�Z����
        float temp = dot(input.Normal, PLightIncidentVec);
        temp *= -1;
        //���ς̌��ʂ�0�ȉ��Ȃ�0�ɂ���
        if (temp < 0.0f)
        {
            temp = 0;
        }
    
        //�g�U���ˌ������߂�
        float3 diffuseLight = CalcLambertDiffuse(PLightIncidentVec, PLightColor, input.Normal);
        //���ʔ��ˌ������߂�
        float3 specularLight = CalcPhongSpecular(PLightIncidentVec, PLightColor, input.Position.xyz, input.Normal);
    
        //���������߂�
        float distance = length(input.Position.xyz - PLightPos);
        //�e���͂��v�Z����
        float power = 1.0f - 1.0f / PLightPower * distance;
        //�e���͂��}�C�i�X�ɂȂ�ꍇ0�ɂ���
        if (power < 0.0f)
        {
            power = 0;
   
        }
    
        //�e���͈͂��i��
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
   
    /*�X�|�b�g���C�g*/
    ////////////////////////////////////////////////////////////////
    
    //�ŏI�I�ɓ����X�|�b�g���C�g�̕ϐ�
    float3 SLight = float3(0, 0, 0);
    
    //�X�|�b�g���C�g�̌v�Z
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

        //���������̍i��
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
        

        //���̕����ɂ�錸���̍i��
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
/// Lambert�g�U���ˌ����v�Z����
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    // �s�N�Z���̖@���ƃ��C�g�̕����̓��ς��v�Z����
    float t = dot(normal, lightDirection) * -1.0f;

    t = (t + 1) * 0.5;
    
    // ���ς̒l��0�ȏ�̒l�ɂ���
    t = max(0.0f, t);

    // �g�U���ˌ����v�Z����
    return lightColor * t;
}
/// <summary>
/// Phong���ʔ��ˌ����v�Z����
/// </summary>
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // ���˃x�N�g�������߂�
    float3 refVec = reflect(lightDirection, normal);

    // �������������T�[�t�F�C�X���王�_�ɐL�т�x�N�g�������߂�
    float3 toEye = CameraPos - worldPos;
    toEye = normalize(toEye);

    // ���ʔ��˂̋��������߂�
    float t = dot(refVec, toEye);

    t = (t + 1) * 0.5;
    
    // ���ʔ��˂̋�����0�ȏ�̐��l�ɂ���
    t = max(0.0f, t);

    // ���ʔ��˂̋������i��
    t = pow(t, 5.0f);

    // ���ʔ��ˌ������߂�
    return lightColor * t;
}
