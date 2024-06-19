#include "Camera.h"

Camera::Camera():
	m_pos(0,0,0),
	m_target(0,0,1)
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
	SetCameraPositionAndTarget_UpVecY(m_pos.CastVECTOR(), m_target.CastVECTOR());
}