#include "ObjectBase.h"

ObjectBase::ObjectBase(const TCHAR* model,const TCHAR* graph)
{
	m_modelHandle = MV1LoadModel(model);
	m_graphHandle = LoadGraph(graph);
}

ObjectBase::~ObjectBase()
{
	MV1DeleteModel(m_modelHandle);
}

void ObjectBase::Draw()
{
	MV1DrawModel(m_modelHandle);
}
