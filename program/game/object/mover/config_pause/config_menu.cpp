#include "config_menu.h"
#include "../ui_frame.h"


namespace spe {

	void ConfigMenu::onCreatedOfMenuFrame() {

		// メニュー項目の数
		const int MENU_NUM = 7;

		// 描画位置
		const float RENDER_X = -95.0f;
		const float RENDER_START_Y = -165.0f;
		const float RENDER_INTERVAL = 50.0f;

		texts_.resize(MENU_NUM);
		message_file_path_.resize(MENU_NUM);

		// メニュー項目のテキスト
		const std::string MENU_STR[MENU_NUM] = {
			"HOW TO PLAY",
			"ITEM",
			"ENDING",
			"RANKING",
			"VOLUME",
			"RESET",
			"BACK",
		};

		// メッセージウィンドウに表示するテキストのファイルパス
		const std::string MESSAGE_FILE_PATH[MENU_NUM] = {
			"text/config_pause/how_to_play.txt",
			"text/config_pause/item.txt",
			"text/config_pause/ending.txt",
			"text/config_pause/ranking.txt",
			"text/config_pause/volume.txt",
			"text/config_pause/reset.txt",
			"text/config_pause/back.txt",
		};

		for (int i = 0; i < MENU_NUM; ++i) {
			texts_[i] = dxe::Text::create(MENU_STR[i]);
			pushChild(texts_[i]);
			texts_[i]->setActive(false);
			texts_[i]->font_size_ = 30;
			texts_[i]->render_position_from_camera_ = 0.0f;
			texts_[i]->transform_.position_.x = RENDER_X;
			texts_[i]->transform_.position_.y = RENDER_START_Y + (RENDER_INTERVAL * i);

			message_file_path_[i] = MESSAGE_FILE_PATH[i];
		}

		// 一番上の項目を選択状態にするため、色を変更する
		texts_[0]->color_.set(1.0f, 0.0f, 0.0f);

	}

}
