#pragma once
#include "Vector3.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();

	void SetPos(MyEngine::Vector3 pos) { m_pos = pos; }
	void SetTargetPos(MyEngine::Vector3 target) { m_target = target; };

	MyEngine::Vector3 GetLightDir();

	double GetCameraDir();
private:
	MyEngine::Vector3 m_pos;
	MyEngine::Vector3 m_target;
};

