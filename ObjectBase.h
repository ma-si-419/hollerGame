#pragma once
#include "MyEngine.h";
class ObjectBase
{
public:
	ObjectBase(const TCHAR* model,const TCHAR* graph);
	virtual ~ObjectBase();

	void Draw();

	MyEngine::Vector3 GetPos() { return m_pos; }
	int GetHandle() { return m_graphHandle; }

protected:
	MyEngine::Vector3 m_pos;
	int m_modelHandle;
	int m_graphHandle;
};

