#include "CharacterBase.h"

CharacterBase::CharacterBase(const TCHAR* model):
	m_pos()
{
	m_handle = MV1LoadModel(model);
}

CharacterBase::~CharacterBase()
{
	MV1DeleteModel(m_handle);
}
