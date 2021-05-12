//--------------------------------------------------
// Scene
#include "planet.h"
#include "space.h"
#include "epilogue.h"
#include "title.h"

//--------------------------------------------------
// Object
#include "../object/mover/message_window.h"
#include "../object/mover/limited_chase_camera2d.h"
#include "../object/mover/ui.h"
#include "../object/mover/planet_key_item_frame.h"
#include "../object/render_object/background_stars.h"
#include "../object/render_object/planet_map.h"
#include "../object/physics_object/planet_player.h"
#include "../object/collision_object/planet_warp_point.h"
#include "../object/collision_object/planet_key_item.h"
#include "../object/mover/config_pause/pause.h"

//--------------------------------------------------
// その他
#include "../object/debug_command.h"

#include "../timer.h"
#include "../player_status.h"
#include "../save_data.h"


namespace spe {

	void Planet::initialize() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		//----------------------------------------------------------------------------------------------------
		// オブジェクト生成

		// 外部CSVファイルから情報の設定
		std::vector<std::vector<std::string>> info_data = t2k::loadCsv(csv_folder_path_ + "/../info.csv");
		id_ = std::stoi(info_data[0][1]);
		dxe::Physics::getInstance().gravity_ = t2k::Vector3(std::stof(info_data[1][1]), std::stof(info_data[1][2]), std::stof(info_data[1][3]));
		
		// マップ
		// この中で敵、アイテム、ワープポイントを生成している
		PlanetMap::SharedPtr map = PlanetMap::create(csv_folder_path_, warp_points_, key_item_);

		const int MAP_WIDTH = map->getMapWidth();
		const int MAP_HEIGHT = map->getMapHeight();
		const int MAP_CHIP_SIZE = map->getMapChipSize();

		// 星々
		BackgroundStarsDesc stars_desc;
		stars_desc.generate_num_ = 100;
		stars_desc.width_ = MAP_WIDTH;
		stars_desc.height_ = MAP_HEIGHT;
		BackgroundStars::create(stars_desc);

		// 背景
		dxe::Sprite::SharedPtr bg = dxe::Sprite::createFromFile("graphics/bg_back.png");
		bg->alpha_ = 0.5f;
		// 星よりも先に描画する
		bg->render_priority_ = stars_desc.priority_ - 1.0f;
		// 星の半分
		bg->render_position_from_camera_ = stars_desc.render_position_from_camera_ * 0.5f;
		
		// プレイヤー
		player_ = PlanetPlayer::create<PlanetPlayer>();

		// 視界の枠作成
		dxe::Sprite::SharedPtr view = dxe::Sprite::createFromFile("graphics/view.png");
		view->render_position_from_camera_ = 0.0f;
		view->alpha_ = 0.5f;
		view->render_priority_ = 5.0f;

		// UI
		UI::create(csv_folder_path_);

		// プロローグから来た場合
		if (prev_scene_ == "prologue") {
			std::list<PlanetWarpPoint::SharedPtr>::iterator it = warp_points_.begin();
			while (it != warp_points_.end()) {
				if ((*it)->getWarpDestination() == "space") {
					(*it)->destroyWithChild();
					warp_points_.erase(it);
					prev_scene_ = "space_to_planet";
					break;
				}
				++it;
			}
		}

		// 前シーンへのワープポイントがあった場合はそこにPlayerを移動させる
		for (const auto& warp : warp_points_) {
			if (warp->getWarpDestination() != prev_scene_) continue;
			// 同じ座標に移動させるとめり込むため1ブロック分あげる
			player_->transform_.position_ = warp->transform_.position_ + (t2k::Vector3::UP * (float)MAP_CHIP_SIZE);
			break;
		}

		//----------------------------------------------------------------------------------------------------
		// スクリーン作成

		// 範囲内でターゲットを追従するカメラ
		LimitedChaseCamera2DDesc camera_desc;
		camera_desc.chase_position_ = &player_->transform_.position_;
		// マップ外がカメラに映らないように限界を設定
		camera_desc.top_left_limit_ = t2k::Vector3(-MAP_WIDTH * 0.5f + (WINDOW_WIDTH>>1) + MAP_CHIP_SIZE, -MAP_HEIGHT * 0.5f + (WINDOW_HEIGHT>>1) + MAP_CHIP_SIZE, 0);
		camera_desc.bottom_right_limit_ = t2k::Vector3(MAP_WIDTH * 0.5f - (WINDOW_WIDTH>>1) - MAP_CHIP_SIZE, MAP_HEIGHT * 0.5f - (WINDOW_HEIGHT>>1) - MAP_CHIP_SIZE, 0);
		LimitedChaseCamera2D::SharedPtr main_camera = LimitedChaseCamera2D::create(camera_desc);
		main_camera->transform_.position_ = player_->transform_.position_;

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

		se_manager.registSE(dxe::SEKey::JUMP);
		se_manager.registSE(dxe::SEKey::ATTACK);
		se_manager.registSE(dxe::SEKey::DAMAGE);
		se_manager.registSE(dxe::SEKey::WARP);
		se_manager.registSE(dxe::SEKey::ITEM);
		se_manager.registSE(dxe::SEKey::HIT);
		se_manager.registSE(dxe::SEKey::ENERGY);
		se_manager.registSE(dxe::SEKey::PAUSE);
		se_manager.registSE(dxe::SEKey::LIMIT);
		se_manager.registSE(dxe::SEKey::HIT2);
		se_manager.registSE(dxe::SEKey::TACKLE);
		se_manager.registSE(dxe::SEKey::SMOKE);
		se_manager.registSE(dxe::SEKey::PREPARE_TACKLE_1);
		se_manager.registSE(dxe::SEKey::PREPARE_TACKLE_2);

		//----------------------------------------------------------------------------------------------------
		// デバッグコマンド有効化

		DebugCommand::create<DebugCommand>();
		t2k::Debug::log("Planet");

		//----------------------------------------------------------------------------------------------------
	}

	void Planet::lateUpdate() {
		seq_.update();
	}

	void Planet::finalize() {

	}

	bool Planet::seqIdle() {

		Timer& timer = Timer::getInstance();
		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

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

		// 条件でエピローグへ

		// 制限時間に達したら
		if (timer.TIME <= 0.0f) {
			engine.changeScene(Epilogue::create(EndType::BAD_TIME_UP));
		}

		// 画面外（上）
		if (player_->transform_.position_.y < -(engine.getWindowHeight() >> 1)) {
			engine.changeScene(Epilogue::create(EndType::BAD_PLANET_JUMP_OUT));
		}
		// 画面外（下）
		if ((engine.getWindowHeight() >> 1) < player_->transform_.position_.y) {
			engine.changeScene(Epilogue::create(EndType::BAD_PLANET_FALLING));
		}

		// アイテム獲得
		if (player_->isGetKeyItem()) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ITEM);
			seq_.change(&Planet::seqGetKeyItem);
		}

		// すべてのワープポイントについて
		for (const auto& warp : warp_points_) {
			if (!warp->isWarp()) continue;
			dxe::SEManager::getInstance().play(dxe::SEKey::WARP);
			// 宇宙へ
			if (warp->getWarpDestination() == "space") {
				engine.changeScene(Space::create(id_));
				t2k::Debug::log("to Space");
			}
			// 惑星へ
			else {
				engine.changeScene(Planet::create(csv_folder_path_, warp->getWarpDestination()));
			}
			break;
		}

		// ポーズ
		bool pause = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_SPACE);

		if (pause) {
			dxe::SEManager::getInstance().play(dxe::SEKey::PAUSE);
			seq_.change(&Planet::seqPause);
		}

		return true;
	}

	bool Planet::seqGetKeyItem() {

		if (seq_.isStart()) {
			is_update_game_object_ = false;

			// いろいろ生成

			const float PRIORITY = 20.0f;

			blur_ = dxe::Sprite::createFromFile("graphics/blur.png");
			blur_->render_priority_ = PRIORITY;
			blur_->render_position_from_camera_ = 0.0f;
			
			message_window_ = MessageWindow::createFromFile(key_item_->getTextFilePath());
			message_window_->setRenderPriority(PRIORITY);
			message_window_->setActiveCKey(false);
			message_window_->is_update_always_ = true;

			key_item_frame_ = PlanetKeyItemFrame::create(key_item_->getSpriteFilePath());
			key_item_frame_->setRenderPriority(PRIORITY);
			key_item_frame_->is_update_always_ = true;

			hp_text_ = dxe::Text::create("[ HP回復！]");
			hp_text_->transform_.position_ = t2k::Vector3(0.0f, 70.0f, 0.0f);
			hp_text_->color_.set(1.0f, 0.0f, 0.0f);
			hp_text_->font_size_ = 24;
			hp_text_->align_mode_x_ = dxe::AlignModeX::CENTER;
			hp_text_->render_priority_ = PRIORITY;
			hp_text_->render_position_from_camera_ = 0.0f;
			hp_text_->setActive(false);

			return true;
		}

		if (message_window_->isOpen()) {
			hp_text_->setActive(true);
		}
		
		// 再生が終了したらメッセージウィンドウのCキーを有効に
		if (true) {
			message_window_->setActiveCKey(true);
		}

		bool is_key_pressed = false;

		// Cキーが有効になったらキー入力を有効に
		if (message_window_->isActiveCKey()) {

			bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
			bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

			if (enter) {
				dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
				is_key_pressed = true;
			}
			else if (back) {
				dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
				is_key_pressed = true;
			}

		}

		if (is_key_pressed) {
			message_window_->close();
			key_item_frame_->close();
			hp_text_->destroy();
		}

		if (message_window_->isClose()) {
			is_update_game_object_ = true;

			PlayerStatus& status = PlayerStatus::getInstance();
			dxe::DxEngine& engine = dxe::DxEngine::getInstance();

			// 太陽
			if (key_item_->getPlanetID() == PlanetID::SUN) {
				EndType end_type = EndType::GOOD_SURVIVAL;
				// 水星から海王星までのアイテムを獲得しているか確認
				for (int i = 1; i < SaveData::PLANET_MAX - 1; ++i) {
					if (status.hasItem((PlanetID)i)) continue;
					end_type = EndType::BAD_SUN_EXPLOSION;
					break;
				}
				engine.changeScene(Epilogue::create(end_type));
			}
			// 冥王星
			else if (key_item_->getPlanetID() == PlanetID::PLUTO) {
				engine.changeScene(Epilogue::create(EndType::TRUE_PLUTO));
			}
			// その他
			else {
				seq_.change(&Planet::seqIdle);
			}

			key_item_frame_->destroyWithChild();
			message_window_->destroyWithChild();
			blur_->destroy();

			player_->setGetKeyItem(false);
			status.getItem(key_item_->getPlanetID());
			status.changeHP(1);
			key_item_->destroyWithChild();
		}

		return true;
	}

	bool Planet::seqPause() {

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
			seq_.change(&Planet::seqIdle);
		}

		return true;
	}

	Planet::SharedPtr Planet::create(const std::string& prev_scene, const std::string& csv_folder_path) {
		Planet::SharedPtr ptr = dxe::Scene::create<Planet>();
		ptr->prev_scene_ = prev_scene;
		ptr->csv_folder_path_ = csv_folder_path;
		return ptr;
	}

}
