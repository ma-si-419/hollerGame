#pragma once
#include "DxLib.h"
#include <map>
#include <string>
#include <vector>
namespace MyEngine
{
	class Input
	{
	public:
		/// <summary>
		/// �X�e�B�b�N�̌X����ۑ�����\����
		/// </summary>
		struct StickInfo
		{
			int leftStickX;
			int leftStickY;
			int rightStickX;
			int rightStickY;
		};

		Input();

		/// <summary>
		/// ���͏����X�V����
		/// </summary>
		void Update();

		/// <summary>
		/// �L�[���������ǂ���
		/// </summary>
		/// <param name="keyName">���肵�����L�[</param>
		/// <returns>���������ǂ���</returns>
		bool IsPress(const std::string& action)const;

		/// <summary>
		/// �L�[�������ꂽ�u�Ԃ����擾����
		/// </summary>
		/// <param name="action">���肵�����L�[</param>
		/// <returns>�����ꂽ�u�Ԃ̂�true��Ԃ�</returns>
		bool IsTrigger(const std::string& action)const;

		/// <summary>
		/// �X�e�B�b�N�̌X�����擾����
		/// </summary>
		/// <returns>�X�e�B�b�N���ǂꂾ���|��Ă��邩</returns>
		StickInfo GetStickInfo() { return m_stickInfo; }

	private:
		/// <summary>
		/// ���͎��
		/// </summary>
		enum class InputType
		{
			kKeyboard,
			kPad,
			kMouse
		};
		struct InputMapInfo
		{
			InputType type;
			int buttonID;
		};

		std::map<std::string, std::vector<InputMapInfo>> m_inputActionMap;

		std::map<std::string, bool> m_currentInput;
		std::map<std::string, bool> m_lastInput;

		StickInfo m_stickInfo;
	};
}