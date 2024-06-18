#include "SceneGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
SceneGame::SceneGame(SceneManager& sceneManager) : SceneBase(sceneManager)
{
	m_pPlayer = std::make_shared<Player>();
	m_pEnemy = std::make_shared<Enemy>();
	m_pCamera = std::make_shared<Camera>();

	//オリジナルシェーダー使うと宣言
	MV1SetUseOrigShader(true);

	//シェーダーハンドル
	m_psHandle = LoadPixelShader("PixelShader.pso");
	m_vsHandle = LoadVertexShader("VertexShader.vso");

	m_cBuff = CreateShaderConstantBuffer(sizeof(LightData));

	m_lightData = static_cast<LightData*>(GetBufferShaderConstantBuffer(m_cBuff));

	//ポイントライトは実装するかわからないので消しておく
	//ポイントライトの情報を取得する
	{
		m_lightData->PLightPower = 1000;

		m_lightData->PLightPos[0] = m_pPlayer->GetPos().x;
		m_lightData->PLightPos[1] = m_pPlayer->GetPos().y;
		m_lightData->PLightPos[2] = m_pPlayer->GetPos().z;

		m_lightData->PLightColor[0] = 1;
		m_lightData->PLightColor[1] = 1;
		m_lightData->PLightColor[2] = 1;

	}

	//ディレクションライトの情報を設定する
	{

		m_lightData->DLightColor[0] = 0.3f;
		m_lightData->DLightColor[1] = 0.3f;
		m_lightData->DLightColor[2] = 0.3f;

		//m_lightData->DLightColor[0] = 0.0f;
		//m_lightData->DLightColor[1] = 0.8f;
		//m_lightData->DLightColor[2] = 0.5f;

		m_lightData->DLightDir[0] = 0.0;
		m_lightData->DLightDir[1] = -1.0;
		m_lightData->DLightDir[2] = 0.0;

	}

	//スポットライトの情報を設定する
	{

		m_lightData->SpLightPos[0] = m_pPlayer->GetPos().x;
		m_lightData->SpLightPos[1] = m_pPlayer->GetPos().y;
		m_lightData->SpLightPos[2] = m_pPlayer->GetPos().z;

		m_lightData->SpLightColor[0] = 1;
		m_lightData->SpLightColor[1] = 1;
		m_lightData->SpLightColor[2] = 1;

		m_lightData->SpLightDir[0] = m_pPlayer->GetCameraDir().x;
		m_lightData->SpLightDir[1] = m_pPlayer->GetCameraDir().y;
		m_lightData->SpLightDir[2] = m_pPlayer->GetCameraDir().z;

		m_lightData->SpLightAngle = 3.14f / 180 * 25;

		m_lightData->SpLightPower = 3000.0f;

	}
	//カメラの座標を取得する
	{

		m_lightData->CameraPos[0] = m_pPlayer->GetPos().x;
		m_lightData->CameraPos[1] = m_pPlayer->GetPos().y;
		m_lightData->CameraPos[2] = m_pPlayer->GetPos().z;

	}
	SetUseVertexShader(m_vsHandle);
	SetUsePixelShader(m_psHandle);
}

SceneGame::~SceneGame()
{
	m_pPlayer->~Player();
	m_pEnemy->~Enemy();
}

void SceneGame::Init()
{
	m_pPlayer->Init();
	m_pEnemy->Init();
}

void SceneGame::Update(MyEngine::Input input)
{
	m_pPlayer->Update(input);
	m_pEnemy->Update();
	m_pCamera->SetPosAndAngle(m_pPlayer->GetPos(),m_pPlayer->GetCameraDir());
	m_pCamera->Update();
	//ポイントライトの情報を設定する
	{
		m_lightData->PLightPos[0] = m_pPlayer->GetPos().x;
		m_lightData->PLightPos[1] = m_pPlayer->GetPos().y;
		m_lightData->PLightPos[2] = m_pPlayer->GetPos().z;
	}
	//スポットライトの情報を設定する
	{

		m_lightData->SpLightPos[0] = m_pPlayer->GetPos().x;
		m_lightData->SpLightPos[1] = m_pPlayer->GetPos().y;
		m_lightData->SpLightPos[2] = m_pPlayer->GetPos().z;

	/*	m_lightData->SpLightDir[0] = m_pPlayer->GetCameraDir().x;
		m_lightData->SpLightDir[1] = m_pPlayer->GetCameraDir().y;
		m_lightData->SpLightDir[2] = m_pPlayer->GetCameraDir().z;*/

		m_lightData->SpLightDir[0] = 0;
		m_lightData->SpLightDir[1] = 0.5;
		m_lightData->SpLightDir[2] = 1;

		m_lightData->SpLightAngle = 3.14f / 180 * 25;

		m_lightData->SpLightPower = 1000.0f;

	}
	//カメラの座標を取得する
	{

		m_lightData->CameraPos[0] = m_pPlayer->GetPos().x;
		m_lightData->CameraPos[1] = m_pPlayer->GetPos().y;
		m_lightData->CameraPos[2] = m_pPlayer->GetPos().z;

	}
	//シェーダ関係
	UpdateShaderConstantBuffer(m_cBuff);
	SetShaderConstantBuffer(m_cBuff, DX_SHADERTYPE_PIXEL, 4);
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	DrawString(0, 0, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}
