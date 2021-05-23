#include "config_ending.h"
#include "../../../save_data.h"
#include "../ui_frame.h"


namespace spe {

	void ConfigEnding::onCreatedOfMainFrame() {

		SaveData& save_data = SaveData::getInstance();
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/epilogue/epilogue.csv");

		// GOODエンドでクリアしていない場合はTRUEエンドを外す
		const int ENDING_NUM = save_data.isClearEnd(EndType::GOOD_SURVIVAL) ? SaveData::ENDING_MAX : SaveData::ENDING_MAX - 1;
		const float POSITION_X = -300.0f;
		const float POSITION_Y_TOP = -160.0f;
		const int FONT_SIZE = 24;
		const int INTERVAL = 10;

		render_endings_.resize(RENDER_NUM);
		endings_.resize(ENDING_NUM);
		message_file_path_.resize(ENDING_NUM);

		for (int i = 0; i < ENDING_NUM; ++i) {
			// クリアしている場合
			if (save_data.isClearEnd((EndType)i)) {
				endings_[i] = t2k::formatToString("%02d. %s", i + 1, data[i][0].c_str());
				std::vector<std::vector<std::string>> ep_data = t2k::loadCsv(data[i][1]);
				message_file_path_[i] = ep_data[0][1];
			}
			// クリアしていない場合は?????
			else {
				endings_[i] = t2k::formatToString("%02d. ?????", i + 1);
				message_file_path_[i] = "text/config_pause/none_data.txt";
			}
		}

		for (int i = 0; i < RENDER_NUM; ++i) {
			render_endings_[i] = dxe::Text::create(endings_[i]);
			pushChild(render_endings_[i]);
			render_endings_[i]->transform_.position_.x = POSITION_X;
			render_endings_[i]->transform_.position_.y = POSITION_Y_TOP + (i * (FONT_SIZE + INTERVAL));
			render_endings_[i]->render_position_from_camera_ = 0.0f;
			render_endings_[i]->align_mode_x_ = dxe::AlignModeX::LEFT;
			render_endings_[i]->align_mode_y_ = dxe::AlignModeY::MIDDLE;
			render_endings_[i]->font_size_ = FONT_SIZE;
			render_endings_[i]->setActive(false);
		}

		// 一番上の項目を選択済みにするため、色を変える
		render_endings_[0]->color_.set(1.0f, 0.0f, 0.0f);

	}

	void ConfigEnding::onOpenFrame() {

		if (!render_endings_[0]->isActive()) {
			for (const auto& ending : render_endings_) {
				ending->setActive(true);
			}
		}

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);
		bool up = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP);
		bool down = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_DOWN);

		// ジョイパッド
		t2k::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_A);
			back |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_B);
			up |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_DPAD_UP) || joypad->isPressLeftThumbUpTrigger();
			down |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_DPAD_DOWN) || joypad->isPressLeftThumbDownTrigger();
		}

		is_key_pressed_select_ = false;

		// 上限、下限まで選択しきったら選択位置をずらす処理
		if (up && 0 < (start_index_ + select_)) {
			if (select_ == 0) {
				--start_index_;
			}
			else {
				--select_;
			}
			is_key_pressed_select_ = true;
		}
		if (down && (start_index_ + select_) < (int)(endings_.size() - 1)) {
			if (select_ == RENDER_NUM - 1) {
				++start_index_;
			}
			else {
				++select_;
			}
			is_key_pressed_select_ = true;
		}

		if (is_key_pressed_select_) {
			dxe::SEManager::getInstance().play(dxe::SEKey::SELECT);
			for (int i = 0; i < (int)render_endings_.size(); ++i) {
				render_endings_[i]->changeText(endings_[start_index_ + i]);
				render_endings_[i]->color_ = (select_ == i) ? t2k::Color(1.0f, 0.0f, 0.0f) : t2k::Color(1.0f);
			}
		}

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			close();

		}

	}

	void ConfigEnding::onCloseFrame() {
		if (render_endings_[0]->isActive()) {
			for (const auto& ending : render_endings_) {
				ending->setActive(false);
			}
		}

	}

	void ConfigEnding::setRenderPriority(const float priority) {
		frame_->setRenderPriority(priority);
		for (const auto& ending : render_endings_) {
			ending->render_priority_ = priority + 0.0000001f;
		}
	}

}
