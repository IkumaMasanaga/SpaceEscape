//--------------------------------------------------
// Scene
#include "config.h"
#include "title.h"

//--------------------------------------------------
// Object
#include "../object/render_object/background_stars.h"
#include "../object/mover/message_window.h"
#include "../object/mover/config_pause/config_menu.h"
#include "../object/mover/config_pause/config_pause_how_to_play.h"
#include "../object/mover/config_pause/config_item.h"
#include "../object/mover/config_pause/config_ending.h"
#include "../object/mover/config_pause/config_ranking.h"
#include "../object/mover/config_pause/config_pause_volume.h"
#include "../object/mover/config_pause/config_reset.h"

//--------------------------------------------------
// その他
//#include "../object/debug_command.h"


namespace spe {

	void Config::initialize() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		//----------------------------------------------------------------------------------------------------
		// スクリーン作成

		dxe::Camera2D::SharedPtr main_camera = dxe::Camera2D::create<dxe::Camera2D>();
		createScreenToScene("main_screen", main_camera, WINDOW_WIDTH, WINDOW_HEIGHT);

		//----------------------------------------------------------------------------------------------------
		// オブジェクト生成

		// 背景
		dxe::Sprite::SharedPtr bg = dxe::Sprite::createFromFile("graphics/bg_back.png");
		bg->alpha_ = 0.5f;

		// 星
		BackgroundStarsDesc bg_desc;
		bg_desc.generate_num_ = 50;
		bg_desc.width_ = WINDOW_WIDTH;
		bg_desc.height_ = WINDOW_HEIGHT;
		BackgroundStars::create(bg_desc);

		// 水星
		dxe::Sprite::SharedPtr sun = dxe::Sprite::createFromFile("graphics/space/01_mercury.png");
		sun->transform_.position_ = t2k::Vector3((float)(WINDOW_WIDTH >> 2), (float)(-WINDOW_HEIGHT >> 2), 0);

		// 惑星
		dxe::Sprite::createFromFile("graphics/bg_planet.png");

		// ぼかし
		dxe::Sprite::createFromFile("graphics/blur.png")->alpha_ = 0.4f;

		// ポーズテキスト
		dxe::Text::SharedPtr pause_text = dxe::Text::create("CONFIG");
		pause_text->transform_.position_.y = -350.0f;
		pause_text->align_mode_x_ = dxe::AlignModeX::CENTER;
		pause_text->font_size_ = 50;

		// メニュー
		menu_frame_ = ConfigMenu::create<ConfigMenu>();
		menu_frame_->transform_.position_ = MENU_FRAME_POSITION;

		// メッセージウィンドウ
		message_window_ = MessageWindow::createFromFile(menu_frame_->getMessageTextFilePath());

		//----------------------------------------------------------------------------------------------------
		// サウンド

		// BGM
		dxe::BGMManager& bgm_manager = dxe::BGMManager::getInstance();
		bgm_manager.registBGM(dxe::BGMKey::CONFIG);

		// SE
		dxe::SEManager& se_manager = dxe::SEManager::getInstance();
		se_manager.registSE(dxe::SEKey::ENTER);
		se_manager.registSE(dxe::SEKey::SELECT);
		se_manager.registSE(dxe::SEKey::BACK);

		// 再生
		bgm_manager.play(dxe::BGMKey::CONFIG);

		//----------------------------------------------------------------------------------------------------
		// デバッグコマンド有効化

		//DebugCommand::create<DebugCommand>();
		//t2k::Debug::log("Prologue");

		//----------------------------------------------------------------------------------------------------
	}

	void Config::lateUpdate() {
		seq_.update();
	}

	void Config::finalize() {
		dxe::BGMManager::getInstance().stop();
	}

	bool Config::seqMenu() {

		if (seq_.isStart()) {
			// メニュー操作を有効に
			menu_frame_->setActive(true);
			message_window_->changeTextFromFile(menu_frame_->getMessageTextFilePath());
		}

		// メッセージウィンドウが開ききっていない時は処理しない
		if (!message_window_->isOpen()) return true;

		// 項目が変更されたらメッセージウィンドウのテキストを変更する
		if (menu_frame_->isKeyPressedSelect()) {
			message_window_->changeTextFromFile(menu_frame_->getMessageTextFilePath());
		}

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// ジョイパッド
		mylib::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_A);
			back |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_B);
		}

		// 決定キーが押されたとき
		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			// メニュー操作を封じる
			menu_frame_->setActive(false);

			switch (menu_frame_->getSelectIndex()) {
			case ConfigMenu::HOW_TO_PLAY:
				seq_.change(&Config::seqHowToPlay);
				break;
			case ConfigMenu::ITEM:
				seq_.change(&Config::seqItem);
				break;
			case ConfigMenu::ENDING:
				seq_.change(&Config::seqEnding);
				break;
			case ConfigMenu::RANKING:
				seq_.change(&Config::seqRanking);
				break;
			case ConfigMenu::VOLUME:
				seq_.change(&Config::seqVolume);
				break;
			case ConfigMenu::RESET:
				seq_.change(&Config::seqReset);
				break;
			case ConfigMenu::BACK:
				dxe::DxEngine::getInstance().changeScene(Title::create<Title>());
				break;
			}
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			dxe::DxEngine::getInstance().changeScene(Title::create<Title>());
		}

		return true;
	}

	bool Config::seqHowToPlay() {

		if (seq_.isStart()) {
			how_to_play_ = ConfigPauseHowToPlay::create<ConfigPauseHowToPlay>();
			how_to_play_->transform_.position_ = MAIN_FRAME_POSITION;
		}

		if (how_to_play_->isClose()) {
			how_to_play_->destroyWithChild();
			how_to_play_ = nullptr;
			seq_.change(&Config::seqMenu);
		}

		return true;
	}

	bool Config::seqItem() {

		if (seq_.isStart()) {
			item_ = ConfigItem::create<ConfigItem>();
			item_->transform_.position_ = MAIN_FRAME_POSITION;
			message_window_->changeTextFromFile(item_->getMessageTextFilePath());
		}

		// 項目が変更されたらメッセージウィンドウのテキストを変更する
		if (item_->isKeyPressedSelect()) {
			message_window_->changeTextFromFile(item_->getMessageTextFilePath());
		}

		if (item_->isClose()) {
			item_->destroyWithChild();
			item_ = nullptr;
			seq_.change(&Config::seqMenu);
		}

		return true;
	}

	bool Config::seqEnding() {

		if (seq_.isStart()) {
			ending_ = ConfigEnding::create<ConfigEnding>();
			ending_->transform_.position_ = MAIN_FRAME_POSITION;
			message_window_->changeTextFromFile(ending_->getMessageTextFilePath());
		}

		// 項目が変更されたらメッセージウィンドウのテキストを変更する
		if (ending_->isKeyPressedSelect()) {
			message_window_->changeTextFromFile(ending_->getMessageTextFilePath());
		}

		if (ending_->isClose()) {
			ending_->destroyWithChild();
			ending_ = nullptr;
			seq_.change(&Config::seqMenu);
		}

		return true;
	}

	bool Config::seqRanking() {

		if (seq_.isStart()) {
			ranking_ = ConfigRanking::create<ConfigRanking>();
			ranking_->transform_.position_ = MAIN_FRAME_POSITION;
		}

		if (ranking_->isClose()) {
			ranking_->destroyWithChild();
			ranking_ = nullptr;
			seq_.change(&Config::seqMenu);
		}

		return true;
	}

	bool Config::seqVolume() {

		if (seq_.isStart()) {
			volume_ = ConfigPauseVolume::create<ConfigPauseVolume>();
			volume_->transform_.position_ = MAIN_FRAME_POSITION;
		}

		if (volume_->isClose()) {
			volume_->destroyWithChild();
			volume_ = nullptr;
			seq_.change(&Config::seqMenu);
		}

		return true;
	}

	bool Config::seqReset() {

		if (seq_.isStart()) {
			reset_ = ConfigReset::create<ConfigReset>();
			reset_->transform_.position_ = MAIN_FRAME_POSITION;
		}

		if (reset_->isClose()) {
			reset_->destroyWithChild();
			reset_ = nullptr;
			seq_.change(&Config::seqMenu);
		}

		return true;
	}

}
