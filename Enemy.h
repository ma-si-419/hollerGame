#pragma once
#include "CharacterBase.h"
class Enemy : public CharacterBase
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw();

	int GetGraphHandle() { return m_graphHandle; }
private:
	int m_graphHandle;
};

