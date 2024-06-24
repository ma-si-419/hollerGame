#pragma once
#include "ObjectBase.h"
class Goal : public ObjectBase
{
public:
	Goal();
	~Goal();

	MyEngine::Vector3 GetPos() { return m_pos; };

	bool IsGoalArea(MyEngine::Vector3 pos);

};

