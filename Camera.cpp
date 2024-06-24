#include "Camera.h"
#include "Vector2.h"
Camera::Camera():
	m_pos(0,0,0),
	m_target(0,0,1)
{
	SetCameraNearFar(3.0, 3000.0f);
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update()
{
	SetCameraPositionAndTarget_UpVecY(m_pos.CastVECTOR(), m_target.CastVECTOR());
}

MyEngine::Vector3 Camera::GetLightDir()
{
	MyEngine::Vector3 ans = m_target - m_pos;

	ans = ans.Normalize();

	return ans;
}