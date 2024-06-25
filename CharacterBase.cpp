#include "CharacterBase.h"

CharacterBase::CharacterBase(const TCHAR* model, const TCHAR* graph):
	m_pos()
{
	m_modelHandle = MV1LoadModel(model);
	m_graphHandle = LoadGraph(graph);
}

CharacterBase::~CharacterBase()
{
	MV1DeleteModel(m_modelHandle);
}
