#pragma once
#include "SceneBase.h"
#include "DxLib.h"
class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& sceneManager);
	~SceneTitle();
	//����������
	void Init();
	//�X�V����
	void Update(MyEngine::Input input);
	//�`�揈��
	void Draw();
	//�I������
	void End();
};