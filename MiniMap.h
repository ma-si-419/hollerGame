#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <List>
class MiniMap
{
public:
	MiniMap();
	~MiniMap();

	void Init();
	void Update();
	void Draw();

	void SetPlayerAngle(double angle) { m_playerAngle = angle; }
	void SetCameraAngle(double angle) { m_cameraAngle = angle; }
	void SetPlayerPos(MyEngine::Vector3 pos) { m_playerPos = pos; }
	void SetPlayerHandle(int handle) { m_playerHandle = handle; }
	void EntryShowObject(MyEngine::Vector3 pos,int handle);
private:
	struct ShowObject
	{
		int graphHandle;
		MyEngine::Vector3 pos;
	};
	//ミニマップの座標
	MyEngine::Vector2 m_pos;
	//プレイヤーの画像ハンドル
	int m_playerHandle;
	//プレイヤーの向いている方向
	double m_playerAngle;
	//カメラの向いている方向
	double m_cameraAngle;
	//プレイヤーの座標
	MyEngine::Vector3 m_playerPos;
	//表示するオブジェクトの配列
	std::list<ShowObject> m_objectList;
};

