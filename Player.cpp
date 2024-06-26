#include "Player.h"

using namespace MyEngine;

namespace
{
	//プレイヤーの基本的な移動速度
	constexpr float kSpeed = 5.0f;
}

Player::Player() :
	CharacterBase("data/model/Player.mv1","data/image/miniMapPlayer.png"),
	m_cameraDir(0, 0, 0)
{

}

Player::~Player()
{

}

void Player::Init()
{

}

void Player::Update(Input input)
{
	m_pos.y = 40;
	//スティックの情報を取得
	Input::StickInfo stick = input.GetStickInfo();

	//プレイヤーの移動方向ベクトル
	Vector3 dirVec(stick.leftStickX, 0, -stick.leftStickY);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d,%d", stick.leftStickX, stick.leftStickY);

	if (dirVec.sqLength() != 0)
	{
		m_moveDir = dirVec;

		MATRIX mat = MGetRotY(m_cameraDir.y);

		m_moveDir = m_moveDir.MatTransform(mat);

		dirVec = dirVec.Normalize();

		Vector3 moveVec = dirVec * kSpeed;

		moveVec = moveVec.MatTransform(mat);

		m_pos += moveVec;
	}

	MV1SetPosition(m_modelHandle, m_pos.CastVECTOR());

	//カメラのアングルを変える
	if (input.IsPress("LB"))
	{
		m_cameraDir.y -= 0.05f;
	}
	if (input.IsPress("RB"))
	{
		m_cameraDir.y += 0.05f;
	}


}

void Player::Draw()
{
	MV1DrawModel(m_modelHandle);
}

MyEngine::Vector3 Player::GetCameraTarget()
{
	Vector3 targetVec(0,-3,30);
	
	//カメラの方向に合わせて動く方向を変化させる
	MATRIX mat = MGetRotY(m_cameraDir.y);

	targetVec = targetVec.MatTransform(mat);

	Vector3 ans = m_pos + targetVec;

	return ans;
}

double Player::GetPlayerDir()
{
	return atan2(m_moveDir.x, m_moveDir.z);;
}

