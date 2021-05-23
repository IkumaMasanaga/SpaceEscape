//--------------------------------------------------
// Scene
#include "title.h"
#include "prologue.h"
#include "space.h"
#include "config.h"
#include "demo_movie.h"

//--------------------------------------------------
// Object
#include "../object/render_object/background_stars.h"

//--------------------------------------------------
// その他
//#include "../object/debug_command.h"


namespace spe {

	void Title::initialize() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		engine.setTransitionCompleteTime(0.3f);
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
		bg->render_priority_ = -2.0f;

		// 星々
		BackgroundStarsDesc desc;
		desc.generate_num_ = 50;
		desc.width_ = WINDOW_WIDTH;
		desc.height_ = WINDOW_HEIGHT;
		BackgroundStars::create(desc);

		// 惑星
		dxe::Sprite::createFromFile("graphics/bg_planet.png");

		// タイトルテキスト
		dxe::Text::SharedPtr title = dxe::Text::create("SPACE ESCAPE");
		title->font_size_ = 80;
		title->transform_.position_ = t2k::Vector3(0, -50, 0);
		title->align_mode_x_ = dxe::AlignModeX::CENTER;
		title->align_mode_y_ = dxe::AlignModeY::MIDDLE;

		dxe::Text::SharedPtr sub_title_1 = dxe::Text::create("　太陽系　　　　　　　　");
		sub_title_1->font_size_ = 30;
		sub_title_1->color_.set(1.0f, 0.0f, 0.0f);
		sub_title_1->align_mode_x_ = dxe::AlignModeX::CENTER;
		sub_title_1->align_mode_y_ = dxe::AlignModeY::MIDDLE;
		dxe::Text::SharedPtr sub_title_2 = dxe::Text::create("～　　　から脱出せよ！～");
		sub_title_2->font_size_ = 30;
		sub_title_2->align_mode_x_ = dxe::AlignModeX::CENTER;
		sub_title_2->align_mode_y_ = dxe::AlignModeY::MIDDLE;

		// C押すテキスト
		press_c_ = dxe::Text::create("PRESS [ C ] TO START");
		press_c_->transform_.position_ = t2k::Vector3(0, 250, 0);
		press_c_->font_size_ = 30;
		press_c_->align_mode_x_ = dxe::AlignModeX::CENTER;
		press_c_->align_mode_y_ = dxe::AlignModeY::MIDDLE;

		// 選択項目の総数
		const int SELECT_NUM = 3;

		// 選択項目の文字列
		const std::string SELECT_STR[SELECT_NUM] = {
			"START",
			"CONFIG",
			"EXIT",
		};

		// 選択項目の一番上のY座標
		const int SELECT_POSITION_Y = 200;

		// 選択項目の幅
		const int SELECT_INTERVAL = 50;

		select_texts_.resize(SELECT_NUM);

		// 選択項目の生成
		select_parent_ = dxe::Mover::create<dxe::Mover>();

		for (int i = 0; i < SELECT_NUM; ++i) {
			select_texts_[i] = dxe::Text::create(SELECT_STR[i]);
			select_texts_[i]->transform_.position_ = t2k::Vector3(0, (float)(SELECT_POSITION_Y + SELECT_INTERVAL * i), 0);
			select_texts_[i]->font_size_ = 30;
			select_texts_[i]->align_mode_x_ = dxe::AlignModeX::CENTER;
			select_texts_[i]->align_mode_y_ = dxe::AlignModeY::MIDDLE;
			select_parent_->pushChild(select_texts_[i]);
		}

		// 操作ヒントテキスト
		dxe::Text::SharedPtr operation_select = dxe::Text::create("[ C ] SELECT");
		operation_select->transform_.position_ = t2k::Vector3(300, 350, 0);
		operation_select->font_size_ = 24;
		operation_select->align_mode_x_ = dxe::AlignModeX::CENTER;
		operation_select->align_mode_y_ = dxe::AlignModeY::MIDDLE;
		select_parent_->pushChild(operation_select);

		dxe::Text::SharedPtr operation_back = dxe::Text::create("[ X ] BACK");
		operation_back->transform_.position_ = t2k::Vector3(-300, 350, 0);
		operation_back->font_size_ = 24;
		operation_back->align_mode_x_ = dxe::AlignModeX::CENTER;
		operation_back->align_mode_y_ = dxe::AlignModeY::MIDDLE;
		select_parent_->pushChild(operation_back);

		//----------------------------------------------------------------------------------------------------
		// サウンド

		// BGM
		dxe::BGMManager& bgm_manager = dxe::BGMManager::getInstance();
		bgm_manager.registBGM(dxe::BGMKey::TITLE);

		// SE
		dxe::SEManager& se_manager = dxe::SEManager::getInstance();
		se_manager.registSE(dxe::SEKey::ENTER);
		se_manager.registSE(dxe::SEKey::SELECT);
		se_manager.registSE(dxe::SEKey::BACK);

		// 再生
		bgm_manager.play(dxe::BGMKey::TITLE);

		//----------------------------------------------------------------------------------------------------
		// デバッグコマンド有効化

		//DebugCommand::create<DebugCommand>();
		//t2k::Debug::log("Title");

		//----------------------------------------------------------------------------------------------------
	}

	void Title::lateUpdate() {
		if (!seq_.update()) return;
		// BGMの再生が終わったらデモムービーを流す
		if (!dxe::BGMManager::getInstance().isPlaying(dxe::BGMKey::TITLE)) {
			dxe::DxEngine::getInstance().changeScene(DemoMovie::create<DemoMovie>());
		}
	}

	void Title::finalize() {
		dxe::BGMManager::getInstance().stop();
	}

	bool Title::seqPressC() {

		// シーケンス開始時
		if (seq_.isStart()) {
			press_c_->setActive(true);
			select_parent_->setActiveWithChild(false);
		}

		// シーン遷移中は入力を受け付けない
		if (dxe::DxEngine::getInstance().isInTransition()) return false;

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);

		// ジョイパッド
		t2k::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_A);
		}

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			seq_.change(&Title::seqSelectMenu);
		}

		return true;
	}

	bool Title::seqSelectMenu() {

		// シーケンス開始時
		if (seq_.isStart()) {
			press_c_->setActive(false);
			select_parent_->setActiveWithChild(true);
			// 選択項目の色を一度白に戻す
			for (const auto& text : select_texts_) {
				text->color_.set(1.0f);
			}
			// 選択を一番上にして色を変更する
			selected_ = 0;
			select_texts_[0]->color_.set(1.0f, 0.0f, 0.0f);
		}

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		// シーン遷移中はプレイヤーの入力を受け付けない
		if (engine.isInTransition()) return false;

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

		if (up && 0 < selected_) {
			--selected_;
			is_key_pressed = true;
		}
		if (down && selected_ < select_texts_.size() - 1) {
			++selected_;
			is_key_pressed = true;
		}

		// 選択項目が切り替わったら
		if (is_key_pressed) {
			dxe::SEManager::getInstance().play(dxe::SEKey::SELECT);
			for (unsigned int i = 0; i < select_texts_.size(); ++i) {
				// 選択中の項目は色を変える
				select_texts_[i]->color_ = (i == selected_) ? t2k::Color(1.0f, 0.0f, 0.0f) : t2k::Color(1.0f);
			}
		}

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			switch (selected_) {
			case SELECT_START:
				engine.changeScene(Prologue::create<Prologue>());
				break;
			case SELECT_CONFIG:
				engine.changeScene(Config::create<Config>());
				break;
			case SELECT_EXIT:
				engine.exitGame();
				break;
			}
		}
		else if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			seq_.change(&Title::seqPressC);
		}

		return true;
	}

}
