#pragma once
#include "DxLib.h"
#include "../shared_factory.h"


namespace mylib {

	class JoypadXInput final : public t2k::SharedFactory<JoypadXInput> {
	public:
		using SharedPtr = std::shared_ptr<JoypadXInput>;
		using WeakPtr = std::weak_ptr<JoypadXInput>;
	private:
		int input_type_;
		XINPUT_STATE prev_state_;
		XINPUT_STATE now_state_;
	public:
		enum ButtonType {
			BUTTON_A,
			BUTTON_B,
			BUTTON_Y,
			BUTTON_X,
			BUTTON_DPAD_UP,
			BUTTON_DPAD_DOWN,
			BUTTON_DPAD_LEFT,
			BUTTON_DPAD_RIGHT,
			BUTTON_LEFT_SHOULDER,
			BUTTON_RIGHT_SHOULDER,
			BUTTON_LEFT_THUMB,
			BUTTON_RIGHT_THUMB,
			BUTTON_START,
			BUTTON_BACK,
			BUTTON_MAX
		};

		// 更新
		void update();

		// 押されているか
		bool isPressButton(ButtonType button) const;
		float getLeftTriggerValue() const;
		float getRightTriggerValue() const;
		float getLeftThumbXValue() const;
		float getLeftThumbYValue() const;
		float getRightThumbXValue() const;
		float getRightThumbYValue() const;

		// 押されたか
		bool isPressButtonTrigger(ButtonType button) const;
		bool isPressLeftTriggerTrigger(const float press_value = 1.0f) const;
		bool isPressRightTriggerTrigger(const float press_value = 1.0f) const;
		bool isPressLeftThumbUpTrigger(const float press_value = 1.0f) const;
		bool isPressLeftThumbDownTrigger(const float press_value = -1.0f) const;
		bool isPressLeftThumbLeftTrigger(const float press_value = 1.0f) const;
		bool isPressLeftThumbRightTrigger(const float press_value = -1.0f) const;
		bool isPressRightThumbUpTrigger(const float press_value = 1.0f) const;
		bool isPressRightThumbDownTrigger(const float press_value = -1.0f) const;
		bool isPressRightThumbLeftTrigger(const float press_value = 1.0f) const;
		bool isPressRightThumbRightTrigger(const float press_value = -1.0f) const;

		// 離されたか
		bool isReleaseButtonTrigger(ButtonType button) const;
		bool isReleaseLeftTriggerTrigger(const float release_value = 0.0f) const;
		bool isReleaseRightTriggerTrigger(const float release_value = 0.0f) const;
		bool isReleaseLeftThumbUpTrigger(const float release_value = 0.0f) const;
		bool isReleaseLeftThumbDownTrigger(const float release_value = 0.0f) const;
		bool isReleaseLeftThumbLeftTrigger(const float release_value = 0.0f) const;
		bool isReleaseLeftThumbRightTrigger(const float release_value = 0.0f) const;
		bool isReleaseRightThumbUpTrigger(const float release_value = 0.0f) const;
		bool isReleaseRightThumbDownTrigger(const float release_value = 0.0f) const;
		bool isReleaseRightThumbLeftTrigger(const float release_value = 0.0f) const;
		bool isReleaseRightThumbRightTrigger(const float release_value = 0.0f) const;

		// 生成
		static JoypadXInput::SharedPtr create(const int input_type);
	};

}
