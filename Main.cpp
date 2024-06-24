#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "Input.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	bool isWindow = true;

	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(isWindow);

	SetGraphMode(1280, 960,16);

	SetChangeScreenModeGraphicsSystemResetFlag(false);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);


	SceneManager scene;
	MyEngine::Input input;
	scene.ChangeScene(std::make_shared<SceneTitle>(scene));

	scene.Init();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		
		//���͏��̍X�V
		input.Update();
		//�Z���N�g�{�^���������ꂽ��E�B���h�E���[�h��؂�ւ���
		if (input.IsTrigger("SELECT"))
		{
			isWindow = !isWindow;
			ChangeWindowMode(isWindow);
		}
		//�V�[���̍X�V
		scene.Update(input);
		//�V�[���̕`��
		scene.Draw();


		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}