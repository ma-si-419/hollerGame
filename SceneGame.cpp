#include "SceneGame.h"
#include "SceneTitle.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Stage.h"
#include "Goal.h"
#include "MiniMap.h"
SceneGame::SceneGame(SceneManager& sceneManager) : SceneBase(sceneManager)
{
	m_pPlayer = std::make_shared<Player>();
	m_pEnemy = std::make_shared<Enemy>();
	m_pStage = std::make_shared<Stage>();
	m_pGoal = std::make_shared<Goal>();
	m_pMiniMap = std::make_shared<MiniMap>();
	m_pCamera = std::make_shared<Camera>();

	//�I���W�i���V�F�[�_�[�g���Ɛ錾
	MV1SetUseOrigShader(true);

	//�V�F�[�_�[�n���h��
	m_psHandle = LoadPixelShader("PixelShader.pso");
	m_vsHandle = LoadVertexShader("VertexShader.vso");

	m_cBuff = CreateShaderConstantBuffer(sizeof(LightData));

	m_lightData = static_cast<LightData*>(GetBufferShaderConstantBuffer(m_cBuff));


	SetUseVertexShader(m_vsHandle);
	SetUsePixelShader(m_psHandle);
}

SceneGame::~SceneGame()
{
	m_pPlayer->~Player();
	m_pEnemy->~Enemy();
	m_pStage->~Stage();
	m_pGoal->~Goal();
}

void SceneGame::Init()
{
	m_pPlayer->Init();
	m_pEnemy->Init();
	m_pMiniMap->Init();
	InitLightData();
}

void SceneGame::Update(MyEngine::Input input)
{
	//�v���C���[
	m_pPlayer->Update(input);
	//�G�l�~�[
	m_pEnemy->Update();
	//�J����
	m_pCamera->SetPos(m_pPlayer->GetPos());
	m_pCamera->SetTargetPos(m_pPlayer->GetCameraTarget());
	m_pCamera->Update();
	//�~�j�}�b�v
	m_pMiniMap->SetPlayerAngle(m_pPlayer->GetPlayerDir());
	m_pMiniMap->SetCameraAngle(m_pPlayer->GetCameraDir());
	m_pMiniMap->SetPlayerPos(m_pPlayer->GetPos());
	m_pMiniMap->EntryShowObject(m_pGoal->GetPos(), m_pGoal->GetHandle());
	m_pMiniMap->Update();
	if (input.IsTrigger("OK"))
	{
		//�v���C���[���A�N�V�����ł�����W�ɂ��邩����
		bool isGoal = m_pGoal->IsGoalArea(m_pPlayer->GetPos());
		//�v���C���[���S�[��������
		if (isGoal)
		{
			m_sceneManager.ChangeScene(std::make_shared<SceneTitle>(m_sceneManager));
			return;
		}
	}
	//���C�g�̏��̍X�V
	UpdateLightData();

	//�V�F�[�_�֌W
	UpdateShaderConstantBuffer(m_cBuff);
	SetShaderConstantBuffer(m_cBuff, DX_SHADERTYPE_PIXEL, 4);
}

void SceneGame::Draw()
{
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	m_pStage->Draw();
	m_pGoal->Draw();
	m_pMiniMap->Draw();

	DrawString(0, 0, "SceneGame", GetColor(255, 255, 255));
}

void SceneGame::End()
{
}

void SceneGame::InitLightData()
{
	//�|�C���g���C�g�̏����擾����
	{
		m_lightData->PLightPower = 1000;

		m_lightData->PLightPos[0] = m_pGoal->GetPos().x;
		m_lightData->PLightPos[1] = m_pGoal->GetPos().y;
		m_lightData->PLightPos[2] = m_pGoal->GetPos().z;

		m_lightData->PLightColor[0] = 1;
		m_lightData->PLightColor[1] = 1;
		m_lightData->PLightColor[2] = 0.2;

	}

	//�f�B���N�V�������C�g�̏���ݒ肷��
	{

		m_lightData->DLightColor[0] = 0.04f;
		m_lightData->DLightColor[1] = 0.04f;
		m_lightData->DLightColor[2] = 0.04f;

		m_lightData->DLightDir[0] = 0.0;
		m_lightData->DLightDir[1] = -1.0;
		m_lightData->DLightDir[2] = 0.0;

	}

	//�X�|�b�g���C�g�̏���ݒ肷��
	{

		m_lightData->SpLightPos[0] = m_pPlayer->GetPos().x;
		m_lightData->SpLightPos[1] = m_pPlayer->GetPos().y;
		m_lightData->SpLightPos[2] = m_pPlayer->GetPos().z;

		m_lightData->SpLightColor[0] = 1;
		m_lightData->SpLightColor[1] = 1;
		m_lightData->SpLightColor[2] = 1;

		m_lightData->SpLightDir[0] = m_pCamera->GetLightDir().x;
		m_lightData->SpLightDir[1] = m_pCamera->GetLightDir().y;
		m_lightData->SpLightDir[2] = m_pCamera->GetLightDir().z;

		m_lightData->SpLightAngle = 3.14f / 180 * 90;

		m_lightData->SpLightPower = 3000.0f;

	}
	//�J�����̍��W���擾����
	{

		m_lightData->CameraPos[0] = m_pPlayer->GetPos().x;
		m_lightData->CameraPos[1] = m_pPlayer->GetPos().y;
		m_lightData->CameraPos[2] = m_pPlayer->GetPos().z;

	}
}

void SceneGame::UpdateLightData()
{
	//�|�C���g���C�g�̏���ݒ肷��
	{
		m_lightData->PLightPos[0] = m_pGoal->GetPos().x;
		m_lightData->PLightPos[1] = m_pGoal->GetPos().y + 200;
		m_lightData->PLightPos[2] = m_pGoal->GetPos().z;
	}
	//�X�|�b�g���C�g�̏���ݒ肷��
	{

		m_lightData->SpLightPos[0] = m_pPlayer->GetPos().x;
		m_lightData->SpLightPos[1] = m_pPlayer->GetPos().y - 20;
		m_lightData->SpLightPos[2] = m_pPlayer->GetPos().z;

		m_lightData->SpLightDir[0] = m_pCamera->GetLightDir().x;
		m_lightData->SpLightDir[1] = m_pCamera->GetLightDir().y;
		m_lightData->SpLightDir[2] = m_pCamera->GetLightDir().z;

		m_lightData->SpLightAngle = 3.14f / 180 * 20;

		m_lightData->SpLightPower = 1500.0f;

	}
	//�J�����̍��W���擾����
	{

		m_lightData->CameraPos[0] = m_pPlayer->GetPos().x;
		m_lightData->CameraPos[1] = m_pPlayer->GetPos().y;
		m_lightData->CameraPos[2] = m_pPlayer->GetPos().z;

	}
}
