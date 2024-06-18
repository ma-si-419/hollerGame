#pragma once
#include "SceneBase.h"
#include "DxLib.h"
class SceneTitle : public SceneBase
{
public:
	SceneTitle(SceneManager& sceneManager);
	~SceneTitle();
	//‰Šú‰»ˆ—
	void Init();
	//XVˆ—
	void Update(MyEngine::Input input);
	//•`‰æˆ—
	void Draw();
	//I—¹ˆ—
	void End();
};