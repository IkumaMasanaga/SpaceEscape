#include "joypad_manager.h"


namespace dxe {

	void JoypadManager::update() {

		// ジョイパッドが接続されている数が0の場合
		if (GetJoypadNum() == 0) {
			if (joypad_) {
				joypad_ = nullptr;
			}
			return;
		}

		// ジョイパッドが接続されている場合は更新する
		if (joypad_) {
			joypad_->update();
			return;
		}

		for (int i = DX_INPUT_PAD1; i < DX_INPUT_PAD16 + 1; ++i) {
			if (!CheckJoypadXInput(i)) continue;
			joypad_ = t2k::JoypadXInput::create(i);
			return;
		}

	}

}
