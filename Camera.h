#pragma once
#include "Vector3.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();

	void SetPosAndAngle(MyEngine::Vector3 pos,MyEngine::Vector3 angle);

private:
	MyEngine::Vector3 m_pos;
	MyEngine::Vector3 m_angle;
};

