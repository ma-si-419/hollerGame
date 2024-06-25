#pragma once
#include "MyEngine.h"
class CharacterBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CharacterBase(const TCHAR* model, const TCHAR* graph);
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

	/// <summary>
	/// �~�j�}�b�v�ɕ\������摜�n���h����Ԃ�
	/// </summary>
	/// <returns>�摜�n���h��</returns>
	int GetGraphHandle() { return m_graphHandle; }
protected:
	//�\�����W
	MyEngine::Vector3 m_pos;
	//���f���n���h��
	int m_modelHandle;
	//�~�j�}�b�v�ɕ\������摜�n���h��
	int m_graphHandle;
};

