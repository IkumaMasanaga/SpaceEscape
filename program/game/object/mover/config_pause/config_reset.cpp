#include "config_reset.h"
#include "../../../save_data.h"


namespace spe {

	void ConfigReset::onCreatedOfMainFrame() {

		const int FONT_SIZE = 30;
		const int INTERVAL = 10;

		main_text_ = dxe::Text::createFromFile("text/config_pause/reset_info.txt");
		pushChild(main_text_);
		main_text_->transform_.position_.y = -100.0f;
		main_text_->align_mode_x_ = dxe::AlignModeX::CENTER;
		main_text_->font_size_ = FONT_SIZE;
		main_text_->interval_ = INTERVAL;
		main_text_->setActive(false);

		// 選択項目
		select_texts_.resize(2);

		select_texts_[0] = dxe::Text::create("YES");
		pushChild(select_texts_[0]);
		select_texts_[0]->transform_.position_.y = 0.0f;
		select_texts_[0]->render_position_from_camera_ = -100.0f + (FONT_SIZE + INTERVAL) * 3;
		select_texts_[0]->align_mode_x_ = dxe::AlignModeX::CENTER;
		select_texts_[0]->font_size_ = FONT_SIZE;
		select_texts_[0]->setActive(false);

		select_texts_[1] = dxe::Text::create("NO");
		pushChild(select_texts_[1]);
		select_texts_[1]->transform_.position_.y = select_texts_[0]->transform_.position_.y + FONT_SIZE + INTERVAL;
		select_texts_[1]->render_position_from_camera_ = 0.0f;
		select_texts_[1]->align_mode_x_ = dxe::AlignModeX::CENTER;
		select_texts_[1]->font_size_ = FONT_SIZE;
		select_texts_[1]->setActive(false);

		// NOを選択済にするため色を変更する
		select_texts_[1]->color_.set(1.0f, 0.0f, 0.0f);

	}

	void ConfigReset::onOpenFrame() {
		if (!main_text_->isActive()) {
			main_text_->setActive(true);
			for (const auto& text : select_texts_) {
				text->setActive(true);
			}
		}

		seq_.update();
	}

	void ConfigReset::onCloseFrame() {
		if (main_text_->isActive()) {
			main_text_->setActive(false);
			for (const auto& text : select_texts_) {
				text->setActive(false);
			}
		}
	}

	bool ConfigReset::seqGuide() {

		bool up = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP);
		bool down = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_DOWN);
		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

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
				select_texts_[i]->color_ = (select_ == i) ? t2k::Color(1.0f, 0.0f, 0.0f) : t2k::Color(1.0f);
			}
		}

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			switch (select_) {
			case SELECT_YES:
				seq_.change(&ConfigReset::seqExecution);
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

		return true;
	}

	bool ConfigReset::seqExecution() {

		if (seq_.isStart()) {
			// リセット
			SaveData::getInstance().reset();

			// 選択項目の非表示化
			for (const auto& text : select_texts_) {
				text->setActive(false);
			}

			main_text_->changeTextFromFile("text/config_pause/reset_exec.txt");
		}

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			close();
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			close();
		}

		return true;
	}

	void ConfigReset::setRenderPriority(const float priority) {

		// Configシーンでのみ使用するつもりのため実装なし

	}

}
