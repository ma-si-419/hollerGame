#pragma once
#include "DxLib.h"

namespace MyEngine
{
	struct Vector3
	{
		float x, y, z;

		Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3(int X, int Y, int Z)
		{
			x = static_cast<float>(X);
			y = static_cast<float>(Y);
			z = static_cast<float>(Z);
		}
		Vector3(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}
		Vector3(VECTOR vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}
		/// <summary>
		/// DxLib��VECTOR�ɃL���X�g
		/// </summary>
		/// <returns>VECTOR�^�̃f�[�^</returns>
		VECTOR CastVECTOR()
		{
			VECTOR retVec;

			retVec.x = x;
			retVec.y = y;
			retVec.z = z;

			return retVec;
		}
		/// <summary>
		/// �x�N�g���̒������擾
		/// </summary>
		/// <returns>�x�N�g���̒���</returns>
		float Length() const;

		/// <summary>
		/// �x�N�g���̒�����2����擾
		/// </summary>
		/// <returns>�x�N�g���̒�����2��</returns>
		float sqLength() const;
		/// <summary>
		/// ���K�������x�N�g����Ԃ�
		/// </summary>
		/// <returns>���K�������x�N�g��</returns>
		Vector3 Normalize();
		/// <summary>
		/// 2�x�N�g���̓��ς��o��
		/// </summary>
		/// <param name="right">�v�Z����x�N�g��</param>
		/// <returns>�x�N�g���̓���</returns>
		float Dot(Vector3 right);
		/// <summary>
		/// 2�̃x�N�g���̊O�ς��o��
		/// </summary>
		/// <param name="right">�v�Z����x�N�g��</param>
		/// <returns>�x�N�g���̊O��</returns>
		Vector3 Cross(Vector3 right);
		/// <summary>
		/// �����Ŏ󂯎������]�s����g�p���ĕ��s�ړ�
		/// </summary>
		/// <param name="right">��]�s��</param>
		/// <returns>��]�s��̌����Ă�������𐳖ʂƂ����ړ��x�N�g��</returns>
		Vector3 MatTransform(MATRIX& right);


		/*���Z�q�I�[�o�[���[�h*/
		Vector3 operator+(Vector3 right)const;
		Vector3 operator+=(Vector3 right);
		Vector3 operator-(Vector3 right)const;
		Vector3 operator-=(Vector3 right);
		Vector3 operator*(float right)const;
		Vector3 operator*=(float right);
		Vector3 operator/(float right)const;
		Vector3 operator/=(float right);
		Vector3 operator=(VECTOR right);
	};
}


