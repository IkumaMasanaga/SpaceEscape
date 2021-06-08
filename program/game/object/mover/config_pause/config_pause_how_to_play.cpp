#include "config_pause_how_to_play.h"
#include "../ui_frame.h"


namespace spe {

	void ConfigPauseHowToPlay::onCreatedOfMainFrame() {

		// 各種定数
		const int FONT_SIZE = 24;
		const int INTERVAL = 10;
		const float POSITION_X[2] = {
			-300.0f,
			0.0f,
		};
		const std::string TEXT_FILE_PATH[2] = {
			"text/config_pause/how_to_play_info1.txt",
			"text/config_pause/how_to_play_info2.txt",
		};

		for (int i = 0; i < 2; ++i) {
			texts_[i] = dxe::Text::createFromFile(TEXT_FILE_PATH[i]);
			pushChild(texts_[i]);
			texts_[i]->transform_.position_.x = POSITION_X[i];
			texts_[i]->render_position_from_camera_ = 0;
			texts_[i]->align_mode_x_ = dxe::AlignModeX::LEFT;
			texts_[i]->align_mode_y_ = dxe::AlignModeY::MIDDLE;
			texts_[i]->font_size_ = FONT_SIZE;
			texts_[i]->interval_ = INTERVAL;
			texts_[i]->setActive(false);
		}

	}

	void ConfigPauseHowToPlay::onOpenFrame() {

		if (!texts_[0]->isActive()) {
			for (int i = 0; i < 2; ++i) {
				texts_[i]->setActive(true);
			}
		}

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// ジョイパッド
		mylib::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_A);
			back |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_B);
		}

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			close();
		}

	}

	void ConfigPauseHowToPlay::onCloseFrame() {
		if (texts_[0]->isActive()) {
			for (int i = 0; i < 2; ++i) {
				texts_[i]->setActive(false);
			}
		}
	}

	void ConfigPauseHowToPlay::setRenderPriority(const float priority) {
		frame_->setRenderPriority(priority);
		for (int i = 0; i < 2; ++i) {
			texts_[i]->render_priority_ = priority + 0.0000001f;
		}
	}

}
