#include "Enemy.h"

Enemy::Enemy() :
	CharacterBase("data/model/Enemy.mv1")
{
	m_pos.z = 800;
	m_graphHandle = LoadGraph("data/Image/miniMapEnemy.png");
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	MV1SetPosition(m_handle, m_pos.CastVECTOR());
}

void Enemy::Draw()
{
	MV1DrawModel(m_handle);
}
