#include "config_pause_volume.h"
#include "../../../save_data.h"
#include "../ui_frame.h"
#include "../volume_slider.h"


namespace spe {

	void ConfigPauseVolume::onCreatedOfMainFrame() {

		SaveData& save_data = SaveData::getInstance();

		// スライダー
		bgm_slider_ = VolumeSlider::create(&save_data.bgm_volume_);
		pushChild(bgm_slider_);
		bgm_slider_->transform_.position_.y = -50.0f;
		bgm_slider_->is_update_always_ = true;
		bgm_slider_->setActiveWithChild(false);

		se_slider_ = VolumeSlider::create(&save_data.se_volume_);
		pushChild(se_slider_);
		se_slider_->transform_.position_.y = 80.0f;
		se_slider_->is_update_always_ = true;
		se_slider_->setActiveWithChild(false);

		// テキスト
		const int FONT_SIZE = 24;
		const float POSITION_X = -300.0f;

		texts_.resize(2);

		texts_[0] = dxe::Text::create("BGM");
		pushChild(texts_[0]);
		texts_[0]->transform_.position_ = t2k::Vector3(POSITION_X, -100.0f, 0.0f);
		texts_[0]->render_position_from_camera_ = 0.0f;
		texts_[0]->align_mode_x_ = dxe::AlignModeX::LEFT;
		texts_[0]->font_size_ = FONT_SIZE;
		texts_[0]->setActive(false);

		texts_[1] = dxe::Text::create("SE");
		pushChild(texts_[1]);
		texts_[1]->transform_.position_ = t2k::Vector3(POSITION_X, 30.0f, 0.0f);
		texts_[1]->render_position_from_camera_ = 0.0f;
		texts_[1]->align_mode_x_ = dxe::AlignModeX::LEFT;
		texts_[1]->font_size_ = FONT_SIZE;
		texts_[1]->setActive(false);

		texts_[0]->color_.set(1.0f, 0.0f, 0.0f);

	}

	void ConfigPauseVolume::onOpenFrame() {

		if (!bgm_slider_->isActive()) {
			bgm_slider_->setActiveWithChild(true);
			se_slider_->setActiveWithChild(true);
			for (const auto& text : texts_) {
				text->setActive(true);
			}
		}

		seq_.update();
	}

	void ConfigPauseVolume::onCloseFrame() {
		if (bgm_slider_->isActive()) {
			bgm_slider_->setActiveWithChild(false);
			se_slider_->setActiveWithChild(false);
			for (const auto& text : texts_) {
				text->setActive(false);
			}
		}
	}

	bool ConfigPauseVolume::seqMenu() {

		bool up = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP);
		bool down = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_DOWN);
		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// ジョイパッド
		t2k::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_A);
			back |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_B);
			up |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_DPAD_UP) || joypad->isPressLeftThumbUpTrigger();
			down |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_DPAD_DOWN) || joypad->isPressLeftThumbDownTrigger();
		}

		bool is_key_pressed = false;

		if (up && 0 < select_) {
			--select_;
			is_key_pressed = true;
		}
		if (down && select_ < (int)texts_.size() - 1) {
			++select_;
			is_key_pressed = true;
		}

		if (is_key_pressed) {
			dxe::SEManager::getInstance().play(dxe::SEKey::SELECT);
			// 色を変更する
			for (int i = 0; i < (int)texts_.size(); ++i) {
				texts_[i]->color_ = (select_ == i) ? t2k::Color(1.0f, 0.0f, 0.0f) : t2k::Color(1.0f);
			}
		}

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			switch (select_) {
			case SELECT_BGM:
				seq_.change(&ConfigPauseVolume::seqBGM);
				break;
			case SELECT_SE:
				seq_.change(&ConfigPauseVolume::seqSE);
				break;
			}
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			close();
		}

		return true;
	}

	bool ConfigPauseVolume::seqBGM() {

		if (seq_.isStart()) {
			bgm_slider_->setActiveColor(t2k::Color(1.0f, 0.0f, 0.0f));
		}

		bool left = t2k::Input::isKeyDown(t2k::Input::KEYBORD_LEFT);
		bool right = t2k::Input::isKeyDown(t2k::Input::KEYBORD_RIGHT);
		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// ジョイパッド
		t2k::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			left |= joypad->isPressButton(t2k::JoypadXInput::BUTTON_DPAD_LEFT) || joypad->getLeftThumbXValue() < -0.5f;
			right |= joypad->isPressButton(t2k::JoypadXInput::BUTTON_DPAD_RIGHT) || 0.5f < joypad->getLeftThumbXValue();
			enter |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_A);
			back |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_B);
		}

		if (left) {
			SaveData::getInstance().changeBGMVolume(-0.01f);
		}
		if (right) {
			SaveData::getInstance().changeBGMVolume(0.01f);
		}

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			bgm_slider_->setActiveColor(t2k::Color(1.0f));
			seq_.change(&ConfigPauseVolume::seqMenu);
		}

		return true;
	}

	bool ConfigPauseVolume::seqSE() {

		if (seq_.isStart()) {
			se_slider_->setActiveColor(t2k::Color(1.0f, 0.0f, 0.0f));
		}

		bool left = t2k::Input::isKeyDown(t2k::Input::KEYBORD_LEFT);
		bool right = t2k::Input::isKeyDown(t2k::Input::KEYBORD_RIGHT);
		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// ジョイパッド
		t2k::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			left |= joypad->isPressButton(t2k::JoypadXInput::BUTTON_DPAD_LEFT) || joypad->getLeftThumbXValue() < -0.5f;
			right |= joypad->isPressButton(t2k::JoypadXInput::BUTTON_DPAD_RIGHT) || 0.5f < joypad->getLeftThumbXValue();
			enter |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_A);
			back |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_B);
		}

		if (left) {
			SaveData::getInstance().changeSEVolume(-0.01f);
		}
		if (right) {
			SaveData::getInstance().changeSEVolume(0.01f);
		}

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			se_slider_->setActiveColor(t2k::Color(1.0f));
			seq_.change(&ConfigPauseVolume::seqMenu);
		}

		return true;
	}

	void ConfigPauseVolume::setRenderPriority(const float priority) {
		frame_->setRenderPriority(priority);
		bgm_slider_->setRenderPriority(priority + 0.0000001f);
		se_slider_->setRenderPriority(priority + 0.0000001f);
		for (const auto& text : texts_) {
			text->render_priority_ = priority + 0.0000001f;
		}
	}

}
