#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class JoypadManager final : public mylib::Singleton<JoypadManager> {
	private:
		// ���N���X�Ő������邽��
		friend class mylib::Singleton<JoypadManager>;

		JoypadManager() {}

		//====================================================================================================
		// �����o�ϐ�

		mylib::JoypadXInput::SharedPtr joypad_ = nullptr;

		//====================================================================================================
	public:
		~JoypadManager() {}

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update();

		// �W���C�p�b�h�̎擾
		inline mylib::JoypadXInput::SharedPtr getJoypad() const { return joypad_; }

		//====================================================================================================
	};

}
