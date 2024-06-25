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
	//�~�j�}�b�v�̍��W
	MyEngine::Vector2 m_pos;
	//�v���C���[�̉摜�n���h��
	int m_playerHandle;
	//�v���C���[�̌����Ă������
	double m_playerAngle;
	//�J�����̌����Ă������
	double m_cameraAngle;
	//�v���C���[�̍��W
	MyEngine::Vector3 m_playerPos;
	//�\������I�u�W�F�N�g�̔z��
	std::list<ShowObject> m_objectList;
};

