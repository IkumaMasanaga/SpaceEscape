#include "pause_title.h"
#include "../ui_frame.h"


namespace spe {

	void PauseTitle::onCreatedOfMainFrame() {

		const int FONT_SIZE = 30;
		const int INTERVAL = 10;

		dxe::Text::SharedPtr info = dxe::Text::createFromFile("text/config_pause/title_info.txt");
		pushChild(info);
		texts_.emplace_back(info);
		info->transform_.position_.y = -100.0f;
		info->render_position_from_camera_ = 0.0f;
		info->align_mode_x_ = dxe::AlignModeX::CENTER;
		info->font_size_ = FONT_SIZE;
		info->interval_ = INTERVAL;
		info->setActive(false);

		// 選択項目
		select_texts_.resize(2);

		select_texts_[0] = dxe::Text::create("YES");
		pushChild(select_texts_[0]);
		texts_.emplace_back(select_texts_[0]);
		select_texts_[0]->transform_.position_.y = -100.0f + (FONT_SIZE + INTERVAL) * 3;
		select_texts_[0]->render_position_from_camera_ = 0.0f;
		select_texts_[0]->align_mode_x_ = dxe::AlignModeX::CENTER;
		select_texts_[0]->font_size_ = FONT_SIZE;
		select_texts_[0]->setActive(false);

		select_texts_[1] = dxe::Text::create("NO");
		pushChild(select_texts_[1]);
		texts_.emplace_back(select_texts_[1]);
		select_texts_[1]->transform_.position_.y = select_texts_[0]->transform_.position_.y + FONT_SIZE + INTERVAL;
		select_texts_[1]->render_position_from_camera_ = 0.0f;
		select_texts_[1]->align_mode_x_ = dxe::AlignModeX::CENTER;
		select_texts_[1]->font_size_ = FONT_SIZE;
		select_texts_[1]->setActive(false);

		// NOを選択済にするため色を変更する
		select_texts_[1]->color_.set(1.0f, 0.0f, 0.0f);

	}

	void PauseTitle::onOpenFrame() {

		if (!select_texts_[0]->isActive()) {
			for (const auto& text : texts_) {
				text->setActive(true);
			}
		}

		bool up = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP);
		bool down = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_DOWN);
		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// ジョイパッド
		mylib::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_A);
			back |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_B);
			up |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_DPAD_UP) || joypad->isPressLeftThumbUpTrigger();
			down |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_DPAD_DOWN) || joypad->isPressLeftThumbDownTrigger();
		}

		bool is_key_pressed = false;

		if (up && 0 < select_) {
			--select_;
			is_key_pressed = true;
		}
		if (down && select_ < (int)select_texts_.size() - 1) {
			++select_;
			is_key_pressed = true;
		}

		if (is_key_pressed) {
			dxe::SEManager::getInstance().play(dxe::SEKey::SELECT);
			// 色を変更する
			for (int i = 0; i < (int)select_texts_.size(); ++i) {
				select_texts_[i]->color_ = (select_ == i) ? mylib::Color(1.0f, 0.0f, 0.0f) : mylib::Color(1.0f);
			}
		}

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			switch (select_) {
			case SELECT_YES:
				to_title_ = true;
				break;
			case SELECT_NO:
				close();
				break;
			}
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			close();
		}

	}

	void PauseTitle::onCloseFrame() {
		if (select_texts_[0]->isActive()) {
			for (const auto& text : texts_) {
				text->setActive(false);
			}
		}
	}

	void PauseTitle::setRenderPriority(const float priority) {
		frame_->setRenderPriority(priority);
		for (const auto& text : texts_) {
			text->render_priority_ = priority + 0.0000001f;
		}
	}

}
