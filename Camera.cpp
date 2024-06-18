#include "Camera.h"

Camera::Camera():
	m_pos(0,0,0),
	m_angle(0,0,0)
{
	SetCameraNearFar(1.0, 2000.0f);
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update()
{
	SetCameraPositionAndAngle(m_pos.CastVECTOR(), m_angle.x, m_angle.y, m_angle.z);
}

void Camera::SetPosAndAngle(MyEngine::Vector3 pos, MyEngine::Vector3 angle)
{
	m_pos = pos;
	m_angle = angle;
}

