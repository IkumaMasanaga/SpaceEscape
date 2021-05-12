#include "config_item.h"
#include "../../../save_data.h"
#include "../ui_frame.h"


namespace spe {

	void ConfigItem::onCreatedOfMainFrame() {

		SaveData& save_data = SaveData::getInstance();
		std::vector<std::vector<std::string>> data = t2k::loadCsv("text/config_pause/item_info.csv");

		// GOODエンドでクリアしていない場合は冥王星を外す
		const int ITEM_NUM = save_data.isClearEnd(EndType::GOOD_SURVIVAL) ? SaveData::PLANET_MAX : SaveData::PLANET_MAX - 1;
		const float POSITION_X = -300.0f;
		const float POSITION_Y_TOP = -160.0f;
		const int FONT_SIZE = 24;
		const int INTERVAL = 10;

		items_.resize(ITEM_NUM);
		message_file_path_.resize(ITEM_NUM);

		for (int i = 0; i < ITEM_NUM; ++i) {
			// 獲得していない場合は?????
			items_[i] = dxe::Text::create(save_data.hasItem((PlanetID)i) ? t2k::formatToString("%02d. %s", i, data[i][1].c_str()) : t2k::formatToString("%02d. ?????", i));
			pushChild(items_[i]);
			items_[i]->transform_.position_.x = POSITION_X;
			items_[i]->transform_.position_.y = POSITION_Y_TOP + (i * (FONT_SIZE + INTERVAL));
			items_[i]->render_position_from_camera_ = 0.0f;
			items_[i]->align_mode_x_ = dxe::AlignModeX::LEFT;
			items_[i]->align_mode_y_ = dxe::AlignModeY::MIDDLE;
			items_[i]->font_size_ = FONT_SIZE;
			items_[i]->setActive(false);
			// 獲得していない場合は?????のファイル
			message_file_path_[i] = (save_data.hasItem((PlanetID)i)) ? data[i][2] : "text/config_pause/none_data.txt";
		}

		// 一番上の項目を選択済みにするため、色を変える
		items_[0]->color_.set(1.0f, 0.0f, 0.0f);

	}

	void ConfigItem::onOpenFrame() {

		if (!items_[0]->isActive()) {
			for (const auto& item : items_) {
				item->setActive(true);
			}
		}

		bool up = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP);
		bool down = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_DOWN);
		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		is_key_pressed_select_ = false;

		if (up && 0 < select_) {
			--select_;
			is_key_pressed_select_ = true;
		}
		if (down && select_ < (int)items_.size() - 1) {
			++select_;
			is_key_pressed_select_ = true;
		}

		if (is_key_pressed_select_) {
			dxe::SEManager::getInstance().play(dxe::SEKey::SELECT);
			// 色を変更する
			for (int i = 0; i < (int)items_.size(); ++i) {
				items_[i]->color_ = (select_ == i) ? t2k::Color(1.0f, 0.0f, 0.0f) : t2k::Color(1.0f);
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

	void ConfigItem::onCloseFrame() {
		if (items_[0]->isActive()) {
			for (const auto& item : items_) {
				item->setActive(false);
			}
		}
	}

	void ConfigItem::setRenderPriority(const float priority) {
		frame_->setRenderPriority(priority);
		for (const auto& item : items_) {
			item->render_priority_ = priority + 0.0000001f;
		}
	}

}
