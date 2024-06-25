#include "Enemy.h"

Enemy::Enemy() :
	CharacterBase("data/model/Enemy.mv1", "data/Image/miniMapEnemy.png")
{
	m_pos.z = 800;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	MV1SetPosition(m_modelHandle, m_pos.CastVECTOR());
}

void Enemy::Draw()
{
	MV1DrawModel(m_modelHandle);
}
