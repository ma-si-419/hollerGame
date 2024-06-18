#pragma once
#include "MyEngine.h"
class CharacterBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CharacterBase(const TCHAR* model);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CharacterBase();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() = 0;
protected:
	//�\�����W
	MyEngine::Vector3 m_pos;
	//���f���n���h��
	int m_handle;
};

