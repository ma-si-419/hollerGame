#include "MiniMap.h"
#include "Game.h"
#include "DxLib.h"
#include "Vector3.h"
namespace
{
	//ミニマップの大きさ
	constexpr int kMapSize = 105;
	//余白の大きさ
	constexpr int kWindowSpace = 20;
	//ミニマップの座標
	const MyEngine::Vector2 kBasePos(Game::kWindowWidth - kMapSize - kWindowSpace, kMapSize + kWindowSpace);
	//ミニマップのプレイヤーの大きさ
	constexpr double kPlayerScale = 0.75;
	//ミニマップのプレイヤー以外のオブジェクトの大きさ
	constexpr double kObjectScale = 1.0;
	//どのくらいの高さから物を見ているか
	constexpr float kMapHeight = 5.0f;
}

MiniMap::MiniMap() :
	m_pos(0, 0),
	m_playerHandle(-1),
	m_playerAngle(0.0),
	m_cameraAngle(0.0)
{
}

MiniMap::~MiniMap()
{
}

void MiniMap::Init()
{
	m_pos = kBasePos;
}

void MiniMap::Update()
{
}

void MiniMap::Draw()
{
	DrawRotaGraph(kBasePos.x, kBasePos.y, kPlayerScale, m_playerAngle - m_cameraAngle, m_playerHandle, true);
	DrawCircle(kBasePos.x, kBasePos.y, kMapSize, GetColor(255, 255, 255), false);
	for (auto& item : m_objectList)
	{
		MyEngine::Vector3 toItem = item.pos - m_playerPos;

		MATRIX mat = MGetRotY(-m_cameraAngle);

		toItem = toItem.MatTransform(mat);

		toItem /= kMapHeight;

		MyEngine::Vector2 drawPos(toItem.x, -toItem.z);

		//マップの外にいたら描画しない
		float length = drawPos.Length();
		DrawFormatString(200, 0, GetColor(255, 255, 255), "%f", length);
		if (length < kMapSize + 15)
		{
			DrawRotaGraph(kBasePos.x + drawPos.x, kBasePos.y + drawPos.y, kObjectScale, 0.0, item.graphHandle, true);
		}
	}


	m_objectList.clear();
}

void MiniMap::EntryShowObject(MyEngine::Vector3 pos, int handle)
{
	ShowObject entryObject;

	entryObject.pos = pos;
	entryObject.graphHandle = handle;

	m_objectList.push_back(entryObject);
}
