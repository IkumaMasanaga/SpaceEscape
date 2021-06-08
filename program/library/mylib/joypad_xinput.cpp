#include "joypad_xinput.h"


namespace mylib {

	static int buttons[JoypadXInput::BUTTON_MAX] = {
		XINPUT_BUTTON_A,				// BUTTON_A,
		XINPUT_BUTTON_B,				// BUTTON_B,
		XINPUT_BUTTON_Y,				// BUTTON_Y,
		XINPUT_BUTTON_X,				// BUTTON_X,
		XINPUT_BUTTON_DPAD_UP,			// BUTTON_DPAD_UP,
		XINPUT_BUTTON_DPAD_DOWN,		// BUTTON_DPAD_DOWN,
		XINPUT_BUTTON_DPAD_LEFT,		// BUTTON_DPAD_LEFT,
		XINPUT_BUTTON_DPAD_RIGHT,		// BUTTON_DPAD_RIGHT,
		XINPUT_BUTTON_LEFT_SHOULDER,	// BUTTON_LEFT_SHOULDER,
		XINPUT_BUTTON_RIGHT_SHOULDER,	// BUTTON_RIGHT_SHOULDER,
		XINPUT_BUTTON_LEFT_THUMB,		// BUTTON_LEFT_THUMB,
		XINPUT_BUTTON_RIGHT_THUMB,		// BUTTON_RIGHT_THUMB,
		XINPUT_BUTTON_START,			// BUTTON_START,
		XINPUT_BUTTON_BACK,				// BUTTON_BACK,
	};

	void JoypadXInput::update() {

		// 前フレームの入力状況を記録
		for (int i = 0; i < JoypadXInput::BUTTON_MAX; ++i) {
			prev_state_.Buttons[buttons[i]] = now_state_.Buttons[buttons[i]];
		}
		prev_state_.LeftTrigger = now_state_.LeftTrigger;
		prev_state_.RightTrigger = now_state_.RightTrigger;
		prev_state_.ThumbLX = now_state_.ThumbLX;
		prev_state_.ThumbLY = now_state_.ThumbLY;
		prev_state_.ThumbRX = now_state_.ThumbRX;
		prev_state_.ThumbRY = now_state_.ThumbRY;
		
		// 現在の入力状況の取得
		GetJoypadXInputState(input_type_, &now_state_);
	}

	bool JoypadXInput::isPressButton(ButtonType button) const {
		return now_state_.Buttons[buttons[button]];
	}

	bool JoypadXInput::isPressButtonTrigger(ButtonType button) const {
		return now_state_.Buttons[buttons[button]] && (now_state_.Buttons[buttons[button]] != prev_state_.Buttons[buttons[button]]);
	}

	bool JoypadXInput::isReleaseButtonTrigger(ButtonType button) const {
		return prev_state_.Buttons[buttons[button]] && (now_state_.Buttons[buttons[button]] != prev_state_.Buttons[buttons[button]]);
	}

	bool JoypadXInput::isPressLeftTriggerTrigger(const float press_value) const {
		return (press_value <= (now_state_.LeftTrigger / 255.0f)) && ((prev_state_.LeftTrigger / 255.0f) < press_value);
	}

	bool JoypadXInput::isReleaseLeftTriggerTrigger(const float release_value) const {
		return ((now_state_.LeftTrigger / 255.0f) <= release_value) && (release_value < (prev_state_.LeftTrigger / 255.0f));
	}

	bool JoypadXInput::isPressRightTriggerTrigger(const float press_value) const {
		return (press_value <= (now_state_.RightTrigger / 255.0f)) && ((prev_state_.RightTrigger / 255.0f) < press_value);
	}

	bool JoypadXInput::isReleaseRightTriggerTrigger(const float release_value) const {
		return ((now_state_.RightTrigger / 255.0f) <= release_value) && (release_value < (prev_state_.RightTrigger / 255.0f));
	}

	float JoypadXInput::getLeftTriggerValue() const {
		return now_state_.LeftTrigger / 255.0f;
	}

	float JoypadXInput::getRightTriggerValue() const {
		return now_state_.RightTrigger / 255.0f;
	}

	bool JoypadXInput::isPressLeftThumbUpTrigger(const float press_value) const {
		return (press_value <= ((now_state_.ThumbLY == -256 ? 0 : now_state_.ThumbLY) / (now_state_.ThumbLY < 0 ? 32768.0f : 32767.0f))) && (((prev_state_.ThumbLY == -256 ? 0 : prev_state_.ThumbLY) / (now_state_.ThumbLY < 0 ? 32768.0f : 32767.0f)) < press_value);
	}

	bool JoypadXInput::isPressLeftThumbDownTrigger(const float press_value) const {
		return (((now_state_.ThumbLY == -256 ? 0 : now_state_.ThumbLY) / (now_state_.ThumbLY < 0 ? 32768.0f : 32767.0f)) <= press_value) && (press_value < ((prev_state_.ThumbLY == -256 ? 0 : prev_state_.ThumbLY) / (now_state_.ThumbLY < 0 ? 32768.0f : 32767.0f)));
	}

	bool JoypadXInput::isPressLeftThumbLeftTrigger(const float press_value) const {
		return (press_value <= (now_state_.ThumbLX / (now_state_.ThumbLX < 0 ? 32768.0f : 32767.0f))) && ((prev_state_.ThumbLX / (now_state_.ThumbLX < 0 ? 32768.0f : 32767.0f)) < press_value);
	}

	bool JoypadXInput::isPressLeftThumbRightTrigger(const float press_value) const {
		return ((now_state_.ThumbLX / (now_state_.ThumbLX < 0 ? 32768.0f : 32767.0f)) <= press_value) && (press_value < (prev_state_.ThumbLX / (now_state_.ThumbLX < 0 ? 32768.0f : 32767.0f)));
	}

	bool JoypadXInput::isReleaseLeftThumbUpTrigger(const float release_value) const {
		return (((now_state_.ThumbLY == -256 ? 0 : now_state_.ThumbLY) / (now_state_.ThumbLY < 0 ? 32768.0f : 32767.0f)) <= release_value) && (release_value < ((prev_state_.ThumbLY == -256 ? 0 : prev_state_.ThumbLY) / (now_state_.ThumbLY < 0 ? 32768.0f : 32767.0f)));
	}

	bool JoypadXInput::isReleaseLeftThumbDownTrigger(const float release_value) const {
		return (release_value <= ((now_state_.ThumbLY == -256 ? 0 : now_state_.ThumbLY) / (now_state_.ThumbLY < 0 ? 32768.0f : 32767.0f))) && (((prev_state_.ThumbLY == -256 ? 0 : prev_state_.ThumbLY) / (now_state_.ThumbLY < 0 ? 32768.0f : 32767.0f)) < release_value);
	}

	bool JoypadXInput::isReleaseLeftThumbLeftTrigger(const float release_value) const {
		return ((now_state_.ThumbLX / (now_state_.ThumbLX < 0 ? 32768.0f : 32767.0f)) <= release_value) && (release_value < (prev_state_.ThumbLX / (now_state_.ThumbLX < 0 ? 32768.0f : 32767.0f)));
	}

	bool JoypadXInput::isReleaseLeftThumbRightTrigger(const float release_value) const {
		return (release_value <= (now_state_.ThumbLX / (now_state_.ThumbLX < 0 ? 32768.0f : 32767.0f))) && ((prev_state_.ThumbLX / (now_state_.ThumbLX < 0 ? 32768.0f : 32767.0f)) < release_value);
	}

	bool JoypadXInput::isPressRightThumbUpTrigger(const float press_value) const {
		return (press_value <= ((now_state_.ThumbRY == -256 ? 0 : now_state_.ThumbRY) / (now_state_.ThumbRY < 0 ? 32768.0f : 32767.0f))) && (((prev_state_.ThumbRY == -256 ? 0 : prev_state_.ThumbRY) / (now_state_.ThumbRY < 0 ? 32768.0f : 32767.0f)) < press_value);
	}

	bool JoypadXInput::isPressRightThumbDownTrigger(const float press_value) const {
		return (((now_state_.ThumbRY == -256 ? 0 : now_state_.ThumbRY) / (now_state_.ThumbRY < 0 ? 32768.0f : 32767.0f)) <= press_value) && (press_value < ((prev_state_.ThumbRY == -256 ? 0 : prev_state_.ThumbRY) / (now_state_.ThumbRY < 0 ? 32768.0f : 32767.0f)));
	}

	bool JoypadXInput::isPressRightThumbLeftTrigger(const float press_value) const {
		return (press_value <= (now_state_.ThumbRX / (now_state_.ThumbRX < 0 ? 32768.0f : 32767.0f))) && ((prev_state_.ThumbRX / (now_state_.ThumbRX < 0 ? 32768.0f : 32767.0f)) < press_value);
	}

	bool JoypadXInput::isPressRightThumbRightTrigger(const float press_value) const {
		return ((now_state_.ThumbRX / (now_state_.ThumbRX < 0 ? 32768.0f : 32767.0f)) <= press_value) && (press_value < (prev_state_.ThumbRX / (now_state_.ThumbRX < 0 ? 32768.0f : 32767.0f)));
	}

	bool JoypadXInput::isReleaseRightThumbUpTrigger(const float release_value) const {
		return (((now_state_.ThumbRY == -256 ? 0 : now_state_.ThumbRY) / (now_state_.ThumbRY < 0 ? 32768.0f : 32767.0f)) <= release_value) && (release_value < ((prev_state_.ThumbRY == -256 ? 0 : prev_state_.ThumbRY) / (now_state_.ThumbRY < 0 ? 32768.0f : 32767.0f)));
	}

	bool JoypadXInput::isReleaseRightThumbDownTrigger(const float release_value) const {
		return (release_value <= ((now_state_.ThumbRY == -256 ? 0 : now_state_.ThumbRY) / (now_state_.ThumbRY < 0 ? 32768.0f : 32767.0f))) && (((prev_state_.ThumbRY == -256 ? 0 : prev_state_.ThumbRY) / (now_state_.ThumbRY < 0 ? 32768.0f : 32767.0f)) < release_value);
	}

	bool JoypadXInput::isReleaseRightThumbLeftTrigger(const float release_value) const {
		return ((now_state_.ThumbRX / (now_state_.ThumbRX < 0 ? 32768.0f : 32767.0f)) <= release_value) && (release_value < (prev_state_.ThumbRX / (now_state_.ThumbRX < 0 ? 32768.0f : 32767.0f)));
	}

	bool JoypadXInput::isReleaseRightThumbRightTrigger(const float release_value) const {
		return (release_value <= (now_state_.ThumbRX / (now_state_.ThumbRX < 0 ? 32768.0f : 32767.0f))) && ((prev_state_.ThumbRX / (now_state_.ThumbRX < 0 ? 32768.0f : 32767.0f)) < release_value);
	}

	float JoypadXInput::getLeftThumbXValue() const {
		return now_state_.ThumbLX / (now_state_.ThumbLX < 0 ? 32768.0f : 32767.0f);
	}

	float JoypadXInput::getLeftThumbYValue() const {
		return (now_state_.ThumbLY == -256 ? 0 : now_state_.ThumbLY) / (now_state_.ThumbLY < 0 ? 32768.0f : 32767.0f);
	}

	float JoypadXInput::getRightThumbXValue() const {
		return now_state_.ThumbRX / (now_state_.ThumbRX < 0 ? 32768.0f : 32767.0f);
	}

	float JoypadXInput::getRightThumbYValue() const {
		return (now_state_.ThumbRY == -256 ? 0 : now_state_.ThumbRY) / (now_state_.ThumbRY < 0 ? 32768.0f : 32767.0f);
	}

	JoypadXInput::SharedPtr JoypadXInput::create(const int input_type) {
		JoypadXInput::SharedPtr ptr = SharedFactory::create<JoypadXInput>();
		ptr->input_type_ = input_type;
		ptr->update();
		return ptr;
	}

}
