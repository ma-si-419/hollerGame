#include "SceneTitle.h"
#include "SceneGame.h"
namespace
{

}
SceneTitle::SceneTitle(SceneManager& sceneManager) :
	SceneBase(sceneManager)
{

}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Init()
{
}

void SceneTitle::Update(MyEngine::Input input)
{
	if (input.IsTrigger("OK"))
	{
		m_sceneManager.ChangeScene(std::make_shared<SceneGame>(m_sceneManager));
	}

}

void SceneTitle::Draw()
{
	DrawString(0, 0, "SceneTitle", GetColor(255, 255, 255));
}

void SceneTitle::End()
{
}