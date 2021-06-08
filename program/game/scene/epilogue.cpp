//--------------------------------------------------
// Scene
#include "epilogue.h"
#include "title.h"

//--------------------------------------------------
// Object
#include "../object/render_object/background_stars.h"
#include "../object/mover/message_window.h"
#include "../object/physics_object/enemy/planet_flame.h"
#include "../object/physics_object/enemy/planet_poison.h"

//--------------------------------------------------
// その他
//#include "../object/debug_command.h"

#include "../player_status.h"
#include "../save_data.h"
#include "../timer.h"


namespace spe {

	void Epilogue::initialize() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		//----------------------------------------------------------------------------------------------------
		// スクリーン作成

		dxe::Camera2D::SharedPtr main_camera = dxe::Camera2D::create<dxe::Camera2D>();
		createScreenToScene("main_screen", main_camera, WINDOW_WIDTH, WINDOW_HEIGHT);

		//----------------------------------------------------------------------------------------------------
		// オブジェクト生成

		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/epilogue/epilogue.csv");
		std::vector<std::vector<std::string>> ep_data = t2k::loadCsv(data[(int)end_type_][1]);

		// 背景
		dxe::Sprite::SharedPtr bg = dxe::Sprite::createFromFile("graphics/bg_back.png");
		bg->alpha_ = 0.5f;

		// 星
		BackgroundStarsDesc bg_desc;
		bg_desc.generate_num_ = 50;
		bg_desc.width_ = WINDOW_WIDTH;
		bg_desc.height_ = WINDOW_HEIGHT;
		BackgroundStars::create(bg_desc);

		// 太陽
		dxe::Sprite::SharedPtr sun = dxe::Sprite::createFromFile(ep_data[2][1]);
		sun->transform_.position_ = t2k::Vector3((float)(-WINDOW_WIDTH >> 2), (float)(-WINDOW_HEIGHT >> 2), 0);

		// 惑星
		dxe::Sprite::createFromFile("graphics/bg_planet.png");

		// ぼかし
		dxe::Sprite::createFromFile("graphics/blur.png")->alpha_ = 0.4f;

		// Unityちゃん
		dxe::Sprite::createFromFile(ep_data[1][1]);

		// BGM登録用キー
		dxe::BGMKey bgm_key = dxe::BGMKey::EPILOGUE_GAME_OVER;

		switch (end_type_) {
			// エンドの種類によって枠を生成する
		case EndType::BAD_SUN_BURNING:
		case EndType::BAD_NEW_WORLD_BURNING:
		case EndType::BAD_SUN_EXPLOSION:
		case EndType::BAD_TIME_UP:
			PlanetFlame::create(0, 0);
			break;
		case EndType::BAD_NEPTUNE_POISON:
		case EndType::BAD_NEW_WORLD_POISON:
			PlanetPoison::create(0, 0);
			break;
			// GOODエンド以上の場合はBGMを変更する
		case EndType::GOOD_NEW_WORLD:
		case EndType::GOOD_SURVIVAL:
		case EndType::TRUE_PLUTO:
			bgm_key = dxe::BGMKey::EPILOGUE_CLEAR;
			break;
		}

		// メッセージウィンドウ
		message_window_ = MessageWindow::createFromFile(ep_data[0][1]);

		//----------------------------------------------------------------------------------------------------
		// サウンド

		// BGM
		dxe::BGMManager& bgm_manager = dxe::BGMManager::getInstance();
		bgm_manager.registBGM(bgm_key);

		// SE
		dxe::SEManager& se_manager = dxe::SEManager::getInstance();
		se_manager.registSE(dxe::SEKey::ENTER);
		se_manager.registSE(dxe::SEKey::BACK);

		// 停止
		bgm_manager.stop();

		// 再生
		bgm_manager.play(bgm_key);

		//----------------------------------------------------------------------------------------------------
		// 記録

		SaveData& save_data = SaveData::getInstance();

		save_data.recordClearEnd(end_type_);
		save_data.recordGetItems(PlayerStatus::getInstance().getItems());

		// ランキングテキストの生成
		dxe::Mover::SharedPtr ranking_text = save_data.createRankingText(end_type_, Timer::getInstance().getClearTime());
		if (ranking_text) {
			ranking_text->transform_.position_ = t2k::Vector3(250.0f, -150.0f, 0.0f);
		}

		//----------------------------------------------------------------------------------------------------
		// デバッグコマンド有効化

		//DebugCommand::create<DebugCommand>();
		//t2k::Debug::log("Epilogue");

		//----------------------------------------------------------------------------------------------------
	}

	void Epilogue::lateUpdate() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		// シーン遷移中は入力を受け付けない
		if (engine.isInTransition()) return;

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// ジョイパッド
		mylib::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_A);
			back |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_B);
		}

		bool is_key_pressed = false;

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			is_key_pressed = true;
		}
		if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			is_key_pressed = true;
		}

		if (is_key_pressed) {
			engine.changeScene(Title::create<Title>());
			message_window_->close();
		}

	}

	void Epilogue::finalize() {
		dxe::BGMManager::getInstance().stop();
	}

	Epilogue::SharedPtr Epilogue::create(const EndType& end_type) {
		Epilogue::SharedPtr ptr = dxe::Scene::create<Epilogue>();
		ptr->end_type_ = end_type;
		return ptr;
	}

}
