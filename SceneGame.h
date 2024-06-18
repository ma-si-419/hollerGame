#pragma once
#include "SceneBase.h"
#include <memory>
class Player;
class Camera;
class Enemy;
class SceneGame : public SceneBase
{
private:
	//�V�F�[�_�ɓn���f�[�^�\����
	struct LightData
	{
		float PLightPos[3];

		float pad1;

		float PLightColor[3];

		float PLightPower;

		float DLightDir[3];

		float pad2;

		float DLightColor[3];

		float pad3;

		float SpLightPos[3];

		float pad4;

		float SpLightColor[3];

		float SpLightPower;

		float SpLightDir[3];

		float SpLightAngle;

		float CameraPos[3];

		float pad5;
	};
public:
	SceneGame(SceneManager& sceneManager);
	~SceneGame();
	/// <summary>
	/// ����������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(MyEngine::Input input);
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
	/// <summary>
	/// �I������
	/// </summary>
	void End();
private:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;
	//�V�F�[�_�[�n���h��
	int m_psHandle;
	int m_vsHandle;

	//C�o�b�t�@
	int m_cBuff;
	//�V�F�[�_�ɑ��郉�C�g�̃f�[�^
	LightData* m_lightData;
};

