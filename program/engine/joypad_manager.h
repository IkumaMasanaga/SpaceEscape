#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class JoypadManager final : public t2k::Singleton<JoypadManager> {
	private:
		// ���N���X�Ő������邽��
		friend class t2k::Singleton<JoypadManager>;

		JoypadManager() {}

		//====================================================================================================
		// �����o�ϐ�

		t2k::JoypadXInput::SharedPtr joypad_ = nullptr;

		//====================================================================================================
	public:
		~JoypadManager() {}

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update();

		// �W���C�p�b�h�̎擾
		inline t2k::JoypadXInput::SharedPtr getJoypad() const { return joypad_; }

		//====================================================================================================
	};

}
