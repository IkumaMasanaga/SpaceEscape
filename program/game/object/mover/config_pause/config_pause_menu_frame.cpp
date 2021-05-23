#include "config_pause_menu_frame.h"
#include "../ui_frame.h"


namespace spe {

	void ConfigPauseMenuFrame::onCreated() {

		UIFrameDesc frame_desc;
		frame_desc.width_ = 250;
		frame_desc.height_ = 400;
		frame_desc.interval_ = 20;
		frame_desc.inner_color_ = t2k::Color(0.5f);

		frame_ = UIFrame::create(frame_desc);
		pushChild(frame_);
		frame_->is_update_always_ = true;

		onCreatedOfMenuFrame();
	}

	void ConfigPauseMenuFrame::update() {

		// 枠が有効な場合（開いている場合）
		if (frame_->isOpen()) {
			if (!texts_[0]->isActive()) {
				for (const auto& text : texts_) {
					text->setActive(true);
				}
			}

			bool up = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP);
			bool down = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_DOWN);

			// ジョイパッド
			t2k::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
			if (joypad) {
				up |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_DPAD_UP) || joypad->isPressLeftThumbUpTrigger();
				down |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_DPAD_DOWN) || joypad->isPressLeftThumbDownTrigger();
			}

			is_key_pressed_select_ = false;

			if (up && 0 < select_) {
				--select_;
				is_key_pressed_select_ = true;
			}
			if (down && select_ < (int)texts_.size() - 1) {
				++select_;
				is_key_pressed_select_ = true;
			}

			if (is_key_pressed_select_) {
				dxe::SEManager::getInstance().play(dxe::SEKey::SELECT);
				// 色を変更する
				for (int i = 0; i < (int)texts_.size(); ++i) {
					texts_[i]->color_ = (select_ == i) ? t2k::Color(1.0f, 0.0f, 0.0f) : t2k::Color(1.0f);
				}
			}

		}
		// 枠が開いていない場合
		else {
			for (const auto& text : texts_) {
				text->setActive(false);
			}
			if (frame_->isClose()) {
				frame_->setActiveWithChild(false);
			}
		}

	}

	void ConfigPauseMenuFrame::open() {
		if (!frame_->isActive()) frame_->setActiveWithChild(true);
		frame_->open();
	}

	void ConfigPauseMenuFrame::close() {
		frame_->close();
	}

	bool ConfigPauseMenuFrame::isOpen() {
		return frame_->isOpen();
	}

	bool ConfigPauseMenuFrame::isClose() {
		return frame_->isClose();
	}

	void ConfigPauseMenuFrame::setRenderPriority(const float render_priority) {
		frame_->setRenderPriority(render_priority);
		for (const auto& text : texts_) {
			text->render_priority_ = render_priority + 0.0000001f;
		}
	}

}
