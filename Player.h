#pragma once
#include "CharacterBase.h"
class Player : public CharacterBase
{
public:
	Player();
	~Player();

	void Init();
	void Update(MyEngine::Input input);
	void Draw();

	MyEngine::Vector3 GetPos() { return m_pos; }
	MyEngine::Vector3 GetCameraTarget();
private:

	MyEngine::Vector3 m_cameraDir;
};

