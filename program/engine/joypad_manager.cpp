#include "joypad_manager.h"


namespace dxe {

	JoypadManager::~JoypadManager() {
		if (joypad_) {
			delete joypad_;
		}
	}

	void JoypadManager::update() {

		// �W���C�p�b�h���ڑ�����Ă��鐔��0�̏ꍇ
		if (GetJoypadNum() == 0) {
			if (joypad_) {
				delete joypad_;
				joypad_ = nullptr;
			}
			return;
		}

		// �W���C�p�b�h���ڑ�����Ă���ꍇ�͍X�V����
		if (joypad_) {
			joypad_->update();
			return;
		}

		for (int i = DX_INPUT_PAD1; i < DX_INPUT_PAD16 + 1; ++i) {
			if (!CheckJoypadXInput(i)) continue;
			joypad_ = new t2k::JoypadXInput(i);
			return;
		}

	}

}