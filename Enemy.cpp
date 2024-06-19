#include "Enemy.h"

Enemy::Enemy() :
	CharacterBase("data/model/Stage.mv1")
{
	m_pos.z = 800;
	MV1SetScale(m_handle, VGet(0.1, 0.1, 0.1));
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
