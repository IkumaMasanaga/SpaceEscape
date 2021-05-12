#include "pause.h"
#include "../message_window.h"
#include "pause_menu.h"
#include "config_pause_how_to_play.h"
#include "pause_item.h"
#include "config_pause_volume.h"
#include "pause_title.h"


namespace spe {

	void Pause::onCreated() {

		// ぼかし
		dxe::Sprite::SharedPtr blur = dxe::Sprite::createFromFile("graphics/blur.png");
		pushChild(blur);
		blur->render_priority_ = PRIORITY;
		blur->render_position_from_camera_ = 0.0f;
		blur->alpha_ = 0.4f;

		// ポーズテキスト
		dxe::Text::SharedPtr pause_text = dxe::Text::create("PAUSE");
		pushChild(pause_text);
		pause_text->transform_.position_.y = -350.0f;
		pause_text->render_priority_ = PRIORITY;
		pause_text->render_position_from_camera_ = 0.0f;
		pause_text->align_mode_x_ = dxe::AlignModeX::CENTER;
		pause_text->font_size_ = 50;

		// メニュー
		menu_frame_ = PauseMenu::create<PauseMenu>();
		pushChild(menu_frame_);
		menu_frame_->transform_.position_ = MENU_FRAME_POSITION;
		menu_frame_->setRenderPriority(PRIORITY);

		// メッセージウィンドウ
		message_window_ = MessageWindow::create("");
		pushChild(message_window_);
		message_window_->is_update_always_ = true;
		message_window_->setRenderPriority(PRIORITY);

	}

	void Pause::update() {
		seq_.update();
	}

	bool Pause::seqMenu() {

		if (seq_.isStart()) {
			menu_frame_->is_update_always_ = true;
			message_window_->changeTextFromFile(menu_frame_->getMessageTextFilePath());
		}

		// 閉じ切ったらポーズ終了
		if (message_window_->isClose()) {
			is_end_ = true;
		}

		// メッセージウィンドウが開ききっていない時は処理しない
		if (!message_window_->isOpen()) return true;
		
		// 項目が変更されたらメッセージウィンドウのテキストを変更する
		if (menu_frame_->isKeyPressedSelect()) {
			message_window_->changeTextFromFile(menu_frame_->getMessageTextFilePath());
		}

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);
		bool pause = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE);

		// 決定キーが押されたとき
		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			switch (menu_frame_->getSelectIndex()) {
			case PauseMenu::BACK:
				closeFrames();
				break;
			case PauseMenu::HOW_TO_PLAY:
				menu_frame_->is_update_always_ = false;
				seq_.change(&Pause::seqHowToPlay);
				break;
			case PauseMenu::ITEM:
				menu_frame_->is_update_always_ = false;
				seq_.change(&Pause::seqItems);
				break;
			case PauseMenu::VOLUME:
				menu_frame_->is_update_always_ = false;
				seq_.change(&Pause::seqVolume);
				break;
			case PauseMenu::TITLE:
				menu_frame_->is_update_always_ = false;
				seq_.change(&Pause::seqTitle);
				break;
			}
		}
		else {
			if (back) {
				dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
				closeFrames();
			}

			if (pause) {
				dxe::SEManager::getInstance().play(dxe::SEKey::PAUSE);
				closeFrames();
			}
		}
		
		return true;
	}

	bool Pause::seqHowToPlay() {

		if (seq_.isStart()) {
			how_to_play_ = ConfigPauseHowToPlay::create<ConfigPauseHowToPlay>();
			how_to_play_->transform_.position_ = MAIN_FRAME_POSITION;
			how_to_play_->setRenderPriority(PRIORITY);
			how_to_play_->is_update_always_ = true;
		}

		if (how_to_play_->isClose()) {
			how_to_play_->destroyWithChild();
			how_to_play_ = nullptr;
			seq_.change(&Pause::seqMenu);
		}

		return true;
	}

	bool Pause::seqItems() {

		if (seq_.isStart()) {
			item_ = PauseItem::create<PauseItem>();
			item_->transform_.position_ = MAIN_FRAME_POSITION;
			item_->setRenderPriority(PRIORITY);
			item_->is_update_always_ = true;
			message_window_->changeTextFromFile(item_->getMessageTextFilePath());
		}

		// 項目が変更されたらメッセージウィンドウのテキストを変更する
		if (item_->isKeyPressedSelect()) {
			message_window_->changeTextFromFile(item_->getMessageTextFilePath());
		}

		if (item_->isClose()){
			item_->destroyWithChild();
			item_ = nullptr;
			seq_.change(&Pause::seqMenu);
		}

		return true;
	}

	bool Pause::seqVolume() {

		if (seq_.isStart()) {
			volume_ = ConfigPauseVolume::create<ConfigPauseVolume>();
			volume_->transform_.position_ = MAIN_FRAME_POSITION;
			volume_->setRenderPriority(PRIORITY);
			volume_->is_update_always_ = true;
		}

		if (volume_->isClose()) {
			volume_->destroyWithChild();
			volume_ = nullptr;
			seq_.change(&Pause::seqMenu);
		}

		return true;
	}

	bool Pause::seqTitle() {

		if (seq_.isStart()) {
			title_ = PauseTitle::create<PauseTitle>();
			title_->transform_.position_ = MAIN_FRAME_POSITION;
			title_->setRenderPriority(PRIORITY);
			title_->is_update_always_ = true;
		}

		if (title_->isClose()) {
			title_->destroyWithChild();
			title_ = nullptr;
			seq_.change(&Pause::seqMenu);
		}

		return true;
	}

	void Pause::closeFrames() {
		menu_frame_->close();
		message_window_->close();
	}

	bool Pause::toTitle() const {
		return (title_) ? title_->toTitle() : false;
	}

}
