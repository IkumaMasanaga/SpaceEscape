//--------------------------------------------------
// Scene
#include "space.h"
#include "planet.h"
#include "epilogue.h"
#include "title.h"

//--------------------------------------------------
// Object
#include "../object/mover/limited_chase_camera2d.h"
#include "../object/render_object/background_stars.h"
#include "../object/collision_object/space_player.h"
#include "../object/collision_object/space_warp_point.h"
#include "../object/mover/ui.h"
#include "../object/mover/config_pause/pause.h"

//--------------------------------------------------
// その他
#include "../object/debug_command.h"

#include "../timer.h"
#include "../player_status.h"
#include "../save_data.h"


namespace spe {

	void Space::initialize() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		// 幅最大値
		const int WIDTH = 10000;
		// 惑星の間隔
		const int INTERVAL = 1000;

		goal_line_ = (WIDTH >> 1) - (INTERVAL >> 2);

		//----------------------------------------------------------------------------------------------------
		// オブジェクト生成

		// 背景
		const std::string& BACKGROUND_FILE_PATH = "graphics/bg_back.png";
		const float BACKGROUND_ALPHA = 0.5f;

		bg1_ = dxe::Sprite::createFromFile(BACKGROUND_FILE_PATH);
		bg1_->render_position_from_camera_ = BACKGROUND_RENDER_POSITION_FROM_CAMERA;
		bg1_->alpha_ = BACKGROUND_ALPHA;
		bg1_->render_priority_ = -2.0f;
		bg2_ = dxe::Sprite::createFromFile(BACKGROUND_FILE_PATH);
		bg2_->render_position_from_camera_ = BACKGROUND_RENDER_POSITION_FROM_CAMERA;
		bg2_->alpha_ = BACKGROUND_ALPHA;
		bg2_->render_priority_ = -2.0f;

		bg_width_ = bg1_->getTexture()->getWidth();

		// 星々
		BackgroundStarsDesc stars_desc;
		stars_desc.generate_num_ = 300;
		stars_desc.width_ = WIDTH;
		stars_desc.height_ = WINDOW_HEIGHT;

		BackgroundStars::create(stars_desc);

		// プレイヤー
		player_ = SpacePlayer::create<SpacePlayer>();

		// プレイヤーが移動可能な範囲
		dxe::CollisionObject::SharedPtr limit = dxe::CollisionObject::create<dxe::CollisionObject>();
		limit->addCollisionRect("top", dxe::CollisionRect::create(WIDTH, 2, t2k::Vector3(0.0f, (float)((-WINDOW_HEIGHT >> 1) - 1), 0.0f)));
		limit->addCollisionRect("bottom", dxe::CollisionRect::create(WIDTH, 2, t2k::Vector3(0.0f, (float)((WINDOW_HEIGHT >> 1) + 1), 0.0f)));
		limit->addCollisionRect("left", dxe::CollisionRect::create(2, WINDOW_HEIGHT, t2k::Vector3((float)((-WIDTH >> 1) - 1), 0.0f, 0.0f)));
		limit->addCollisionRect("right", dxe::CollisionRect::create(2, WINDOW_HEIGHT, t2k::Vector3((float)((WIDTH >> 1) + 1), 0.0f, 0.0f)));

		// ワープポイント
		SaveData& save_data = SaveData::getInstance();
		const int PLANET_NUM = (save_data.isClearEnd(EndType::GOOD_SURVIVAL)) ? SaveData::PLANET_MAX : SaveData::PLANET_MAX - 1;

		warp_points_.resize(PLANET_NUM);

		// 各惑星のファイルパス
		const std::string PLANET_FILE_PATH[SaveData::PLANET_MAX] = {
			"data/scene/space/00_sun.csv",		// 太陽
			"data/scene/space/01_mercury.csv",	// 水星
			"data/scene/space/02_venus.csv",	// 金星
			"data/scene/space/03_earth.csv",	// 地球
			"data/scene/space/04_mars.csv",		// 火星
			"data/scene/space/05_jupiter.csv",	// 木星
			"data/scene/space/06_saturn.csv",	// 土星
			"data/scene/space/07_uranus.csv",	// 天王星
			"data/scene/space/08_neptune.csv",	// 海王星
			"data/scene/space/09_pluto.csv",	// 冥王星
		};

		// 太陽の位置
		const float SUN_POSITION_X = -(WIDTH >> 1) + (INTERVAL >> 1);

		// 惑星の位置
		// constではないが定数扱いとする
		t2k::Vector3 POSITIONS[SaveData::PLANET_MAX];

		for (int i = 0; i < SaveData::PLANET_MAX; ++i) {
			// 太陽の場合は0固定 それ以外は乱数
			const float POSITION_Y = (i == 0) ? 0.0f : t2k::randomRangeF(-300.0f, 300.0f);
			POSITIONS[i] = t2k::Vector3(SUN_POSITION_X + (INTERVAL * i), POSITION_Y, 0.0f);
		}

		for (int i = 0; i < PLANET_NUM; ++i) {
			warp_points_[i] = SpaceWarpPoint::create(PLANET_FILE_PATH[i]);
			warp_points_[i]->transform_.position_ = POSITIONS[i];

			// 前の惑星番号と同じであればプレイヤーの位置を変更させる
			if (prev_planet_id_ != i) continue;
			player_->transform_.position_ = warp_points_[i]->transform_.position_;
		}

		// 視界の枠作成
		dxe::Sprite::SharedPtr view = dxe::Sprite::createFromFile("graphics/view.png");
		view->render_position_from_camera_ = 0.0f;
		view->alpha_ = 0.5f;
		view->render_priority_ = 5.0f;

		view_red_ = dxe::Sprite::createFromFile("graphics/view_red.png");
		view_red_->render_position_from_camera_ = 0.0f;
		view_red_->alpha_ = 0.0f;
		view_red_->render_priority_ = 5.0f;

		red_alpha_controller_.setMethodSin(&red_alpha_, 1.0f, 0.6f);

		// UI
		UI::create("data/scene/space");

		//----------------------------------------------------------------------------------------------------
		// スクリーン作成

		LimitedChaseCamera2DDesc camera_desc;
		camera_desc.chase_position_ = &player_->transform_.position_;
		camera_desc.top_left_limit_ = t2k::Vector3((float)(-(WIDTH >> 1) + (WINDOW_WIDTH >> 1)), 0.0f, 0.0f);
		camera_desc.bottom_right_limit_ = t2k::Vector3((float)((WIDTH >> 1) - (WINDOW_WIDTH >> 1)), 0.0f, 0.0f);

		LimitedChaseCamera2D::SharedPtr main_camera = LimitedChaseCamera2D::create(camera_desc);
		createScreenToScene("main_screen", main_camera, WINDOW_WIDTH, WINDOW_HEIGHT);

		//----------------------------------------------------------------------------------------------------
		// サウンド

		// BGM
		dxe::BGMManager& bgm_manager = dxe::BGMManager::getInstance();
		bgm_manager.registBGM(dxe::BGMKey::PLAY1);
		bgm_manager.registBGM(dxe::BGMKey::PLAY2);

		// SE
		dxe::SEManager& se_manager = dxe::SEManager::getInstance();
		se_manager.registSE(dxe::SEKey::ENTER);
		se_manager.registSE(dxe::SEKey::SELECT);
		se_manager.registSE(dxe::SEKey::BACK);

		se_manager.registSE(dxe::SEKey::WARP);
		se_manager.registSE(dxe::SEKey::PAUSE);
		se_manager.registSE(dxe::SEKey::JET);
		se_manager.registSE(dxe::SEKey::LIMIT);
		se_manager.registSE(dxe::SEKey::WARNING);

		//----------------------------------------------------------------------------------------------------
		// デバッグコマンド有効化

		DebugCommand::create<DebugCommand>();
		t2k::Debug::log("Space");

		//----------------------------------------------------------------------------------------------------
	}

	void Space::lateUpdate() {
		seq_.update();
	}

	void Space::finalize() {

	}

	bool Space::seqPlay() {

		// 背景座標変更
		int bg1_left = (int)(bg1_->transform_.position_.x - (bg_width_ >> 1));
		int bg1_right = (int)(bg1_->transform_.position_.x + (bg_width_ >> 1));
		float player_x = player_->transform_.position_.x * BACKGROUND_RENDER_POSITION_FROM_CAMERA;

		// プレイヤーが背景の中心から右にあるか左にあるかでもう1枚の背景の位置を変更する
		if (bg1_left <= player_x && player_x < bg1_right) {
			if (player_x < bg1_->transform_.position_.x) {
				bg2_->transform_.position_.x = bg1_->transform_.position_.x - bg_width_ - 1;
			}
			else {
				bg2_->transform_.position_.x = bg1_->transform_.position_.x + bg_width_ + 1;
			}
		}
		else {
			if (player_x < bg2_->transform_.position_.x) {
				bg1_->transform_.position_.x = bg2_->transform_.position_.x - bg_width_ - 1;
			}
			else {
				bg1_->transform_.position_.x = bg2_->transform_.position_.x + bg_width_ + 1;
			}
		}

		Timer& timer = Timer::getInstance();
		PlayerStatus& status = PlayerStatus::getInstance();
		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		red_alpha_controller_.isCompleteUpdate();

		// 半分以下を反転させた割合
		// (半分 - 実数) / 半分
		float view_red_alpha = std::clamp(((PlayerStatus::MAX_ENERGY / 2) - status.getEnergy()) / (PlayerStatus::MAX_ENERGY / 2), 0.0f, 1.0f);
		view_red_->alpha_ = red_alpha_ * view_red_alpha;

		// 音も変更する
		if (0.0f < view_red_alpha) {
			warning_time_count_ += t2k::Time::getDeltaTime();
			// 再生間隔
			const float PLAY_INTERVAL = 1.0f;
			if (PLAY_INTERVAL  < warning_time_count_) {
				warning_time_count_ = 0.0f;
				dxe::SEManager& se_manager = dxe::SEManager::getInstance();
				se_manager.getSE(dxe::SEKey::WARNING)->setVolume(view_red_alpha);
				se_manager.play(dxe::SEKey::WARNING);
			}
		}

		// BGM変更
		const float BGM_CHANGE_LIMIT = 60.0f;
		if (timer.TIME < BGM_CHANGE_LIMIT) {
			dxe::BGMManager& bgm_manager = dxe::BGMManager::getInstance();
			if (bgm_manager.isPlaying(dxe::BGMKey::PLAY1)) {
				dxe::SEManager::getInstance().play(dxe::SEKey::LIMIT);
				bgm_manager.stop(dxe::BGMKey::PLAY1);
			}
			else if (!bgm_manager.isPlaying(dxe::BGMKey::PLAY2) && !dxe::SEManager::getInstance().isPlaying(dxe::SEKey::LIMIT)) {
				bgm_manager.play(dxe::BGMKey::PLAY2);
			}
		}

		timer.update();

		// シーン遷移中は入力を受け付けない
		if (engine.isInTransition()) return true;

		// 制限時間に達したら
		if (timer.TIME <= 0.0f) {
			engine.changeScene(Epilogue::create(EndType::BAD_TIME_UP));
		}

		// プレイヤーが死亡したら
		if (player_->isDead()) {
			engine.changeScene(Epilogue::create(EndType::BAD_SPACE_ENERGY));
		}

		// ゴールラインを超えたら
		if (goal_line_ < player_->transform_.position_.x) {

			// 木星のアイテムを持っていなければ
			if (!status.hasItem(PlanetID::JUPITER)) {
				engine.changeScene(Epilogue::create(EndType::BAD_NEW_WORLD_POISON));
			}
			// 海王星のアイテムを持っていなければ
			else if (!status.hasItem(PlanetID::NEPTUNE)) {
				engine.changeScene(Epilogue::create(EndType::BAD_NEW_WORLD_BURNING));
			}
			// 両方持っていれば
			else {
				engine.changeScene(Epilogue::create(EndType::GOOD_NEW_WORLD));
			}

		}

		// ワープポイントすべて
		for (const auto& warp : warp_points_) {
			if (!warp->isWarp()) continue;
			dxe::SEManager::getInstance().play(dxe::SEKey::WARP);
			// 惑星へ
			engine.changeScene(Planet::create("space_to_planet", warp->getWarpDestination()));
			t2k::Debug::log("to Planet");
			break;
		}

		// ポーズ
		bool pause = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE);

		// ジョイパッド
		t2k::JoypadXInput* joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			pause |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_START);
		}

		if (pause) {
			dxe::SEManager::getInstance().play(dxe::SEKey::PAUSE);
			seq_.change(&Space::seqPause);
		}

		return true;
	}

	bool Space::seqPause() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		if (seq_.isStart()) {
			// オブジェクト更新フラグを降ろす
			engine.getNowScene()->is_update_game_object_ = false;
			pause_ = Pause::create<Pause>();
			pause_->is_update_always_ = true;
		}

		// シーン遷移中は入力を受け付けない
		if (engine.isInTransition()) return true;

		// タイトルへ
		if (pause_->toTitle()) {
			engine.changeScene(Title::create<Title>());
		}

		if (pause_->isEnd()) {
			// オブジェクト更新フラグを立てる
			engine.getNowScene()->is_update_game_object_ = true;
			pause_->destroyWithChild();
			seq_.change(&Space::seqPlay);
		}

		return true;
	}

	Space::SharedPtr Space::create(const int prev_planet_id) {
		Space::SharedPtr ptr = dxe::Scene::create<Space>();
		ptr->prev_planet_id_ = prev_planet_id;
		return ptr;
	}

}
