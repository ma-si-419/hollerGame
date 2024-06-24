#include "Stage.h"
#include "DxLib.h"
Stage::Stage() :
	ObjectBase("data/model/Stage.mv1","data/image/player.png")
{
	MV1SetScale(m_modelHandle, VGet(0.1, 0.1, 0.1));
}

Stage::~Stage()
{
}
