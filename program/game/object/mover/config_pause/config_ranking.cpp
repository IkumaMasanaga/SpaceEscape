#include "config_ranking.h"
#include "../../../save_data.h"
#include "../ui_frame.h"


namespace spe {

	void ConfigRanking::onCreatedOfMainFrame() {

		SaveData& save_data = SaveData::getInstance();
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/epilogue/epilogue.csv");

		text_parent_ = dxe::Mover::create<dxe::Mover>();
		pushChild(text_parent_);

		const float POSITION_X = -300.0f;
		const float POSITION_Y_TOP = -160.0f;
		const int FONT_SIZE = 24;
		const int INTERVAL = 10;

		// 新惑星快適エンド
		dxe::Text::SharedPtr good_1 = dxe::Text::create(save_data.isClearEnd(EndType::GOOD_NEW_WORLD) ? t2k::formatToString("%02d. %s", (int)(EndType::GOOD_NEW_WORLD)+1, data[(int)(EndType::GOOD_NEW_WORLD)][0].c_str()) : t2k::formatToString("%02d. ?????", (int)(EndType::GOOD_NEW_WORLD)+1));
		text_parent_->pushChild(good_1);
		good_1->transform_.position_.x = POSITION_X;
		good_1->transform_.position_.y = POSITION_Y_TOP;
		good_1->font_size_ = FONT_SIZE;
		good_1->align_mode_x_ = dxe::AlignModeX::LEFT;
		good_1->align_mode_y_ = dxe::AlignModeY::MIDDLE;

		dxe::Mover::SharedPtr ranking_1 = save_data.createRankingText(EndType::GOOD_NEW_WORLD);
		text_parent_->pushChild(ranking_1);
		ranking_1->transform_.position_.x = POSITION_X;
		ranking_1->transform_.position_.y = POSITION_Y_TOP + (FONT_SIZE + INTERVAL) * 1;

		// 生還エンド
		dxe::Text::SharedPtr good_2 = dxe::Text::create(save_data.isClearEnd(EndType::GOOD_SURVIVAL) ? t2k::formatToString("%02d. %s", (int)(EndType::GOOD_SURVIVAL)+1, data[(int)(EndType::GOOD_SURVIVAL)][0].c_str()) : t2k::formatToString("%02d. ?????", (int)(EndType::GOOD_SURVIVAL)+1));
		text_parent_->pushChild(good_2);
		good_2->transform_.position_.x = POSITION_X;
		good_2->transform_.position_.y = POSITION_Y_TOP + (FONT_SIZE + INTERVAL) * 5;
		good_2->font_size_ = FONT_SIZE;
		good_2->align_mode_x_ = dxe::AlignModeX::LEFT;
		good_2->align_mode_y_ = dxe::AlignModeY::MIDDLE;

		dxe::Mover::SharedPtr ranking_2 = save_data.createRankingText(EndType::GOOD_SURVIVAL);
		text_parent_->pushChild(ranking_2);
		ranking_2->transform_.position_.x = POSITION_X;
		ranking_2->transform_.position_.y = POSITION_Y_TOP + (FONT_SIZE + INTERVAL) * 6;

		text_parent_->setActiveWithChild(false);

	}

	void ConfigRanking::onOpenFrame() {
		if (!text_parent_->isActive()) {
			text_parent_->setActiveWithChild(true);
		}

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			close();
		}

	}

	void ConfigRanking::onCloseFrame() {
		if (text_parent_->isActive()) {
			text_parent_->setActiveWithChild(false);
		}
	}

	void ConfigRanking::setRenderPriority(const float priority) {

		// Configシーンでのみ使用するつもりのため実装なし
	
	}

}
