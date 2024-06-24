#pragma once
#include "DxLib.h"

namespace MyEngine
{
	struct Vector2
	{
		float x, y;

		Vector2()
		{
			x = 0;
			y = 0;
		}

		Vector2(int X, int Y)
		{
			x = static_cast<float>(X);
			y = static_cast<float>(Y);
		}
		Vector2(float X, float Y)
		{
			x = X;
			y = Y;
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
		Vector2 Normalize();

		Vector2 MatTransform(MATRIX& right);

		/*���Z�q�I�[�o�[���[�h*/
		Vector2 operator+(Vector2 right)const;
		Vector2 operator+=(Vector2 right);
		Vector2 operator-(Vector2 right)const;
		Vector2 operator-=(Vector2 right);
		Vector2 operator*(float right)const;
		Vector2 operator*=(float right);
		Vector2 operator/(float right)const;
		Vector2 operator/=(float right);
		Vector2 operator=(Vector2 right);

	};
}