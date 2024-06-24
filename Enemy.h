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
private:
	int m_graphHandle;
};

