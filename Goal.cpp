#include "Goal.h"
namespace
{
	constexpr float kGoalAreaRadius = 150.0f;
}

Goal::Goal():
	ObjectBase("data/model/Goal.mv1","data/image/miniMapPlayer.png")
{
	m_pos = MyEngine::Vector3(0, -50, 500);
	MV1SetScale(m_modelHandle, VGet(100, 100, 100));
	MV1SetPosition(m_modelHandle, m_pos.CastVECTOR());
}

Goal::~Goal()
{
}

bool Goal::IsGoalArea(MyEngine::Vector3 pos)
{
	MyEngine::Vector3 goalPos = m_pos;
	
	goalPos.z -= kGoalAreaRadius;

	float length = MyEngine::Vector3(goalPos - pos).Length();

	if (length < kGoalAreaRadius)
	{
		return true;
	}

	return false;
}
