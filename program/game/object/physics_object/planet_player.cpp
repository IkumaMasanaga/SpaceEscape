#include "planet_player.h"
#include "../../player_status.h"
#include "../../save_data.h"
#include "../../scene/epilogue.h"
#include "../collision_object/planet_player_bullet.h"


namespace spe {

	void PlanetPlayer::onCreated() {

		// アニメーションの生成
		animation_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		pushChild(animation_);
		animation_->render_priority_ = 1.0f;

		// 外部CSVファイルから読み込み
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/player.csv");
		{
			// アニメーションの読み込み
			std::vector<std::vector<std::string>> anim_data = t2k::loadCsv(data[0][1]);
			for (int i = 0; i < (int)anim_data.size(); ++i) {
				animation_->registAnimation(anim_data[i][0], t2k::Texture::createVectorFromFile(anim_data[i][1], std::stoi(anim_data[i][2]), std::stoi(anim_data[i][3]), std::stoi(anim_data[i][4]), std::stoi(anim_data[i][5]), std::stoi(anim_data[i][6])));
				animation_time_.try_emplace(anim_data[i][0], std::stof(anim_data[i][7]));
			}
		}
		animation_->play("idle", animation_time_["idle"], true);

		// 各種パラメータ設定
		gravity_scale_ = std::stof(data[1][1]);
		default_move_power_ = std::stof(data[2][1]);
		air_move_power_ = std::stof(data[3][1]);
		jump_power_ = std::stof(data[4][1]);
		friction_ = default_friction_ = t2k::Vector3(std::stof(data[5][1]), std::stof(data[5][2]), std::stof(data[5][3]));
		attack_friction_ = t2k::Vector3(std::stof(data[6][1]), std::stof(data[6][2]), std::stof(data[6][3]));
		tackle_move_rate_ = std::stof(data[7][1]);

		// 衝突判定矩形生成
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(30, 48, t2k::Vector3(0.0f, 6.0f, 0.0f));
		rect->is_correct_ = true;
		rect->correct_space_.up_ = 0.0f;
		rect->correct_space_.down_ = 0.0f;
		addCollisionRect("player", rect);

		// タックル時のトリガー衝突判定矩形
		tackle_rect_ = dxe::CollisionRect::create(32, 50, t2k::Vector3(0.0f, 6.0f, 0.0f));
		tackle_rect_->is_trigger_ = true;
		tackle_rect_->setActive(false);
		addCollisionRect("tackle", tackle_rect_);

		// エフェクトの描画優先度
		const float EFFECT_RENDER_PRIORITY = 2.0f;

		// タックルチャージ中エフェクト生成構造体
		{
			std::vector<std::vector<std::string>> effect_data = t2k::loadCsv("data/scene/planet/player_tackle_charge.csv");
			tackle_charge_desc_.file_path_ = effect_data[1][0];
			tackle_charge_desc_.all_num_ = std::stoi(effect_data[1][1]);
			tackle_charge_desc_.x_num_ = std::stoi(effect_data[1][2]);
			tackle_charge_desc_.y_num_ = std::stoi(effect_data[1][3]);
			tackle_charge_desc_.width_ = std::stoi(effect_data[1][4]);
			tackle_charge_desc_.height_ = std::stoi(effect_data[1][5]);
			effect_time_tackle_charge_ = std::stof(effect_data[2][1]);
			effect_time_tackle_charge_max_ = std::stof(effect_data[3][1]);
			tackle_charge_desc_.start_alpha_ = std::stof(effect_data[4][1]);
			tackle_charge_desc_.complete_alpha_ = std::stof(effect_data[4][1]);
			tackle_charge_desc_.render_priority_ = EFFECT_RENDER_PRIORITY;
		}
		
		// タックルエフェクト生成構造体
		{
			std::vector<std::vector<std::string>> effect_data = t2k::loadCsv("data/scene/planet/player_tackle.csv");
			tackle_desc_.file_path_ = effect_data[1][0];
			tackle_desc_.all_num_ = std::stoi(effect_data[1][1]);
			tackle_desc_.x_num_ = std::stoi(effect_data[1][2]);
			tackle_desc_.y_num_ = std::stoi(effect_data[1][3]);
			tackle_desc_.width_ = std::stoi(effect_data[1][4]);
			tackle_desc_.height_ = std::stoi(effect_data[1][5]);
			tackle_desc_.alive_time_ = std::stof(effect_data[2][1]);
			tackle_desc_.start_alpha_ = std::stof(effect_data[3][1]);
			tackle_desc_.complete_alpha_ = std::stof(effect_data[3][1]);
			tackle_desc_.render_priority_ = EFFECT_RENDER_PRIORITY;
		}

		// エネルギー獲得エフェクト生成構造体
		{
			std::vector<std::vector<std::string>> effect_data = t2k::loadCsv("data/scene/planet/player_energy.csv");
			energy_desc_.file_path_ = effect_data[1][0];
			energy_desc_.all_num_ = std::stoi(effect_data[1][1]);
			energy_desc_.x_num_ = std::stoi(effect_data[1][2]);
			energy_desc_.y_num_ = std::stoi(effect_data[1][3]);
			energy_desc_.width_ = std::stoi(effect_data[1][4]);
			energy_desc_.height_ = std::stoi(effect_data[1][5]);
			energy_desc_.alive_time_ = std::stof(effect_data[2][1]);
			energy_desc_.start_alpha_ = std::stof(effect_data[3][1]);
			energy_desc_.complete_alpha_ = std::stof(effect_data[3][1]);
			energy_desc_.render_priority_ = EFFECT_RENDER_PRIORITY;
		}

		// 煙エフェクト生成構造体
		{
			std::vector<std::vector<std::string>> effect_data = t2k::loadCsv("data/scene/planet/player_smoke.csv");
			smoke_desc_.file_path_ = effect_data[1][0];
			smoke_desc_.all_num_ = std::stoi(effect_data[1][1]);
			smoke_desc_.x_num_ = std::stoi(effect_data[1][2]);
			smoke_desc_.y_num_ = std::stoi(effect_data[1][3]);
			smoke_desc_.width_ = std::stoi(effect_data[1][4]);
			smoke_desc_.height_ = std::stoi(effect_data[1][5]);
			smoke_desc_.alive_time_ = std::stof(effect_data[2][1]);
			smoke_desc_.complete_alpha_ = std::stof(effect_data[3][1]);
			smoke_desc_.render_priority_ = EFFECT_RENDER_PRIORITY;
		}

		// 軌跡エフェクト
		{
			std::vector<std::vector<std::string>> effect_data = t2k::loadCsv("data/scene/planet/player_locus.csv");			
			std::vector<std::vector<std::string>> file_paths = t2k::loadCsv(effect_data[1][0]);
			locus_file_paths_.resize(file_paths.size());
			for (int i = 0; i < (int)file_paths.size(); ++i) {
				locus_file_paths_[i] = file_paths[i][0];
			}
			locus_desc_.all_num_ = std::stoi(effect_data[1][1]);
			locus_desc_.x_num_ = std::stoi(effect_data[1][2]);
			locus_desc_.y_num_ = std::stoi(effect_data[1][3]);
			locus_desc_.width_ = std::stoi(effect_data[1][4]);
			locus_desc_.height_ = std::stoi(effect_data[1][5]);
			locus_desc_.alive_time_ = std::stof(effect_data[2][1]);
			locus_desc_.complete_alpha_ = std::stof(effect_data[3][1]);
			locus_desc_.start_scale_ = std::stof(effect_data[4][1]);
			locus_desc_.complete_scale_ = std::stof(effect_data[4][1]);
		}

	}
	
	void PlanetPlayer::update() {

		PlayerStatus& status = PlayerStatus::getInstance();

		// アイテムの獲得状況によって重力の影響割合を変更
		if (status.hasItem(PlanetID::MARS) && status.hasItem(PlanetID::URANUS)) {
			gravity_scale_ = 0.5f;
		}
		else if (status.hasItem(PlanetID::MARS) || status.hasItem(PlanetID::URANUS)) {
			gravity_scale_ = 0.75f;
		}
		
		// Y軸方向に速度がついているかで空中か地上か判断する
		move_power_ = (VELOCITY.y != 0) ? air_move_power_ : default_move_power_;

		// seqDeathが設定されている場合はfalseが帰ってくる為、以降の処理をしない
		if (!seq_.update()) return;

		// ジャンプの入力時間での変動
		bool jump = t2k::Input::isKeyReleaseTrigger(t2k::Input::KEYBORD_C);
		if (jump && VELOCITY.y < 0) {
			addForceFrame(t2k::Vector3(0.0f, VELOCITY.y, 0.0f) * -0.5f);
		}

		// 前フレームの補正方向を見て速度を矯正
		if (correct_flag_ & CORRECT_UP)		if (0 < VELOCITY.y) addForceFrame(t2k::Vector3(0.0f, -VELOCITY.y, 0.0f));
		if (correct_flag_ & CORRECT_DOWN)	if (VELOCITY.y < 0) addForceFrame(t2k::Vector3(0.0f, -VELOCITY.y, 0.0f));
		if (correct_flag_ & CORRECT_LEFT)	if (0 < VELOCITY.x) addForceFrame(t2k::Vector3(-VELOCITY.x, 0.0f, 0.0f));
		if (correct_flag_ & CORRECT_RIGHT)	if (VELOCITY.x < 0) addForceFrame(t2k::Vector3(-VELOCITY.x, 0.0f, 0.0f));
		correct_flag_ = 0;

		// 攻撃中以外でデフォルトの摩擦力ではない場合はデフォルトに戻す
		if (animation_->getNowAnimationName() != "attack" &&
			animation_->getNowAnimationName() != "tackle") {
			if (friction_.x != default_friction_.x || friction_.y != default_friction_.y) {
				friction_ = default_friction_;
			}
		}

		can_jump_ = false;

		// 動いている時のみ軌跡を生成する
		if (1.0f < std::abs(VELOCITY.x) || VELOCITY.y) {
			generate_locus_time_count_ += t2k::Time::getDeltaTime();

			// 生成時間
			const float GENERATE_TIME = 0.07f;

			if (GENERATE_TIME < generate_locus_time_count_) {
				generate_locus_time_count_ = 0;

				// 生成
				locus_desc_.file_path_ = locus_file_paths_[t2k::randomRangeI(0, locus_file_paths_.size())];
				locus_desc_.start_position_ = transform_.position_;
				OneShotAnimation::create(locus_desc_);
			}
		}
		else {
			generate_locus_time_count_ = 0;
		}
	}

	void PlanetPlayer::onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		switch (direction) {
		case dxe::CorrectDirection::UP:		correct_flag_ = CORRECT_UP;		break;
		case dxe::CorrectDirection::DOWN:	correct_flag_ = CORRECT_DOWN;	break;
		case dxe::CorrectDirection::LEFT:	correct_flag_ = CORRECT_LEFT;	break;
		case dxe::CorrectDirection::RIGHT:	correct_flag_ = CORRECT_RIGHT;	break;
		}

		// 上に補正 → 地上にいる
		if (direction == dxe::CorrectDirection::UP) {
			can_jump_ = true;
		}
		if (direction == dxe::CorrectDirection::DOWN) {
			// めり込んでしまう為少し下げてる
			transform_.position_ += t2k::Vector3::DOWN;
			addForceTime(t2k::Vector3::DOWN);
		}

		if (!is_damage_) {
			// 敵と衝突
			if (other->getName() == "enemy") {
				// 通常時
				if (!is_tackle_) {
					dxe::SEManager::getInstance().play(dxe::SEKey::DAMAGE);

					// 敵の弾は消す
					if (rect->getName() == "enemy_bullet") {
						other->destroyWithChild();
					}

					PlayerStatus& status = PlayerStatus::getInstance();
					status.changeHP(-3);

					// 死亡
					if (status.getHP() <= 0) {
						// 毒
						if (rect->getName() == "poison") {
							end_type_ = EndType::BAD_NEPTUNE_POISON;
						}
						// 炎
						else if (rect->getName() == "flame") {
							end_type_ = EndType::BAD_SUN_BURNING;
						}
						// その他（敵）
						else {
							end_type_ = EndType::BAD_PLANET_ENEMY;
						}
						seq_.change(&PlanetPlayer::seqDeath);
					}
					// ダメージ
					else {
						seq_.change(&PlanetPlayer::seqDamage);
					}
					
					is_damage_ = true;
				}
			}
		}

		// エネルギー獲得
		if (other->getName() == "energy_item") {

			PlayerStatus& status = PlayerStatus::getInstance();

			if (!status.changeEnergy((status.hasItem(PlanetID::EARTH)) ? ENERGY_RECOVER_VALUE * 2.0f : ENERGY_RECOVER_VALUE)) {
				dxe::SEManager::getInstance().play(dxe::SEKey::ENERGY);
				other->destroyWithChild();

				// エフェクト生成
				animation_->pushChild(OneShotAnimation::create(energy_desc_));
			}
		}

		// キーアイテム獲得
		if (other->getName() == "key_item") {
			is_get_key_item_ = true;
		}

	}

	bool PlanetPlayer::seqIdle() {

		bool left = t2k::Input::isKeyDown(t2k::Input::KEYBORD_LEFT);
		bool right = t2k::Input::isKeyDown(t2k::Input::KEYBORD_RIGHT);
		bool jump = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool attack = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);
		bool attack_action = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_Z);

		// 移動と反転
		if (left ^ right) {
			if (left) {
				animation_->is_flip_y_ = true;
				addForceTime(t2k::Vector3::LEFT * move_power_);
			}
			else {
				animation_->is_flip_y_ = false;
				addForceTime(t2k::Vector3::RIGHT * move_power_);
			}
		}

		PlayerStatus& status = PlayerStatus::getInstance();

		// ジャンプ
		if (jump && can_jump_) {
			dxe::SEManager::getInstance().play(dxe::SEKey::JUMP);
			addForceFrame(t2k::Vector3::UP * jump_power_);
			can_jump_ = false;
		}

		// 攻撃
		if (attack) {
			seq_.change(&PlanetPlayer::seqAttack);
		}

		// 溜め攻撃
		if (attack_action) {
			seq_.change(&PlanetPlayer::seqEnergyActionCharge);
		}

		// y軸に速度がついている（空中）
		if (VELOCITY.y != 0) {
			const int JUMP_UP_LIMIT = -8;
			const int JUMP_MID1_LIMIT = -3;
			const int JUMP_MID2_LIMIT = 3;
			const int JUMP_MID3_LIMIT = 8;

			if (VELOCITY.y < JUMP_UP_LIMIT) {
				if (animation_->getNowAnimationName() != "jump_up") {
					animation_->play("jump_up", animation_time_["jump_up"], true);
				}
			}
			else if (JUMP_UP_LIMIT <= VELOCITY.y && VELOCITY.y < JUMP_MID1_LIMIT) {
				if (animation_->getNowAnimationName() != "jump_middle_1") {
					animation_->play("jump_middle_1", animation_time_["jump_middle_1"], true);
				}
			}
			else if (JUMP_MID1_LIMIT <= VELOCITY.y && VELOCITY.y < JUMP_MID2_LIMIT) {
				if (animation_->getNowAnimationName() != "jump_middle_2") {
					animation_->play("jump_middle_2", animation_time_["jump_middle_2"], true);
				}
			}
			else if (JUMP_MID2_LIMIT <= VELOCITY.y && VELOCITY.y < JUMP_MID3_LIMIT) {
				if (animation_->getNowAnimationName() != "jump_middle_3") {
					animation_->play("jump_middle_3", animation_time_["jump_middle_3"], true);
				}
			}
			else if (JUMP_MID3_LIMIT <= VELOCITY.y) {
				if (animation_->getNowAnimationName() != "jump_fall") {
					animation_->play("jump_fall", animation_time_["jump_fall"], true);
				}
			}
		}
		// 横に動いている
		else if (0.3f < std::abs(VELOCITY.x) || (left ^ right)) {
			if (animation_->getNowAnimationName() != "run") {
				animation_->play("run", animation_time_["run"], true);
			}
		}
		// 何も入力されていない
		else {
			if (animation_->getNowAnimationName() != "idle") {
				animation_->play("idle", animation_time_["idle"], true);
			}
		}

		// 点滅
		flashByDamage();

		return true;
	}

	bool PlanetPlayer::seqAttack() {

		if (seq_.isStart()) {
			friction_ = attack_friction_;
			animation_->play("attack", animation_time_["attack"], false);

			dxe::SEManager::getInstance().play(dxe::SEKey::ATTACK);

			// 弾の生成 向いている方向によって移動ベクトルを返納させる
			PlanetPlayerBullet::create(animation_->is_flip_y_ ? t2k::Vector3::LEFT : t2k::Vector3::RIGHT, getWorldTransform());

			// x軸の速度によって煙だす
			const float SMOKE_CREATE_LIMIT = 1.0f;
			if (SMOKE_CREATE_LIMIT < std::abs(VELOCITY.x)) {
				smoke_desc_.is_flip_y_ = 0 < VELOCITY.x;
				OneShotAnimation::SharedPtr smoke = OneShotAnimation::create(smoke_desc_);
				animation_->pushChild(smoke);
				smoke->setActiveWithChild(false);
				effect_smoke_ = smoke;
			}

			return true;
		}

		// 煙がある場合は地上にいるときだけ有効にする
		if (!effect_smoke_.expired()) {
			if (!effect_smoke_.lock()->isActive() && VELOCITY.y == 0) {
				dxe::SEManager::getInstance().play(dxe::SEKey::SMOKE);
			}
			effect_smoke_.lock()->setActiveWithChild(VELOCITY.y == 0);
		}

		// アニメーションが終了したら待機に戻る
		if (!animation_->isPlaying()) {
			if (!effect_smoke_.expired()) {
				effect_smoke_.lock()->destroyWithChild();
			}
			seq_.change(&PlanetPlayer::seqIdle);
		}

		// 点滅
		flashByDamage();

		return true;
	}
	
	bool PlanetPlayer::seqEnergyActionCharge() {

		PlayerStatus& status = PlayerStatus::getInstance();

		if (seq_.isStart()) {
			friction_ *= 0.5f;
			animation_->play("tackle", animation_time_["tackle"], false);
		}

		bool attack_action = t2k::Input::isKeyDown(t2k::Input::KEYBORD_Z);
		bool jump = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);

		// ジャンプでキャンセル
		// ジャンプ可能（地上にいる）の場合
		if (jump && can_jump_) {
			dxe::SEManager::getInstance().play(dxe::SEKey::JUMP);
			addForceFrame(t2k::Vector3::UP * jump_power_);
			status.resetTempEnergy();
			seq_.change(&PlanetPlayer::seqIdle);
			can_jump_ = false;
		}

		// 最大エネルギー消費量
		const float CHARGE_MAX = 50.0f;

		// エネルギー増加量
		const float INCREASE = 0.5f;

		// 仮消費エネルギーに足していく
		status.changeTempEnergy((CHARGE_MAX < status.getTempEnergy() + INCREASE) ? CHARGE_MAX - status.getTempEnergy() : INCREASE);

		// キーを離したら実行する
		if (!attack_action) {
			seq_.change(&PlanetPlayer::seqEnergyActionAttack);
		}

		// エフェクト
		if (effect_tackle_.expired()) {
			// 仮消費エネルギーの溜まり具合で生存時間を変更する
			tackle_charge_desc_.alive_time_ = (status.getTempEnergy() == CHARGE_MAX) ? effect_time_tackle_charge_max_ : effect_time_tackle_charge_;
			dxe::SEManager::getInstance().play((tackle_charge_desc_.alive_time_ == effect_time_tackle_charge_max_) ? dxe::SEKey::PREPARE_TACKLE_2 : dxe::SEKey::PREPARE_TACKLE_1);
			OneShotAnimation::SharedPtr charge = OneShotAnimation::create(tackle_charge_desc_);
			animation_->pushChild(charge);
			effect_tackle_ = charge;
		}

		// 点滅
		flashByDamage();

		return true;
	}

	bool PlanetPlayer::seqEnergyActionAttack() {

		PlayerStatus& status = PlayerStatus::getInstance();

		if (seq_.isStart()) {
			animation_->play("run", animation_time_["run"], true);
			// 衝突判定を有効に
			tackle_rect_->setActive(true);
			// 初速をつける
			addForceFrame((animation_->is_flip_y_ ? t2k::Vector3::LEFT : t2k::Vector3::RIGHT) * air_move_power_);
			// 溜めてる途中のエフェクトがのこっている場合は消す
			if (!effect_tackle_.expired()) {
				effect_tackle_.lock()->destroyWithChild();
			}
			is_tackle_ = true;
		}

		// 向きによって移動方向を変える
		addForceTime((animation_->is_flip_y_ ? t2k::Vector3::LEFT : t2k::Vector3::RIGHT) * move_power_ * tackle_move_rate_);

		// エネルギー減少量
		const float DECREASE = 1.0f;

		// 仮消費エネルギーに溜めていたエネルギーを反映させる
		status.reflectTempEnergy(DECREASE);
		
		// 仮消費エネルギーがなくなったらIdleに戻る
		if (status.getTempEnergy() <= 0.0f) {
			seq_.change(&PlanetPlayer::seqIdle);
			// 衝突判定を無効に
			tackle_rect_->setActive(false);
			is_tackle_ = false;
		}

		// SE
		tackle_se_count_ += t2k::Time::getDeltaTime();
		// SE呼び出し間隔
		const float TACKLE_SE_INTERVAL = 0.05f;
		if (TACKLE_SE_INTERVAL < tackle_se_count_) {
			tackle_se_count_ = 0.0f;
			dxe::SEManager::getInstance().play(dxe::SEKey::TACKLE);
		}

		// エフェクト
		if (effect_tackle_.expired()) {
			OneShotAnimation::SharedPtr tackle = OneShotAnimation::create(tackle_desc_);
			animation_->pushChild(tackle);
			effect_tackle_ = tackle;
		}

		// 軌跡の追加生成
		locus_desc_.file_path_ = locus_file_paths_[t2k::randomRangeI(0, locus_file_paths_.size())];
		locus_desc_.start_position_ = transform_.position_ + t2k::Vector3::UP * t2k::randomRangeF(10, 15);
		OneShotAnimation::create(locus_desc_);
		locus_desc_.file_path_ = locus_file_paths_[t2k::randomRangeI(0, locus_file_paths_.size())];
		locus_desc_.start_position_ = transform_.position_ + t2k::Vector3::DOWN * t2k::randomRangeF(10, 15);
		OneShotAnimation::create(locus_desc_);

		// 点滅
		flashByDamage();

		return true;
	}

	bool PlanetPlayer::seqDamage() {
		
		if (seq_.isStart()) {

			// 仮消費エネルギーのリセット
			PlayerStatus::getInstance().resetTempEnergy();

			// 速度をリセット
			addForceFrame(VELOCITY * -1.0f);

			// ノックバックベクトルの生成
			// 向いている方向と逆に飛ばす
			const float NOCK_BACK_Y = 9.0f;
			const float NOCK_BACK_X = 3.0f;
			t2k::Vector3 nock_back = t2k::Vector3::UP * NOCK_BACK_Y;
			nock_back += (((animation_->is_flip_y_) ? t2k::Vector3::RIGHT : t2k::Vector3::LEFT) * NOCK_BACK_X);
			addForceFrame(nock_back);

			// アニメーション切り替え
			animation_->play("damage", animation_time_["damage"], false);

			return true;
		}

		if (!animation_->isPlaying()) {
			seq_.change(&PlanetPlayer::seqIdle);
		}

		// 点滅
		flashByDamage();

		return true;
	}

	bool PlanetPlayer::seqDeath() {
		
		if (seq_.isStart()) {
			animation_->play("death", animation_time_["death"], false);
			return false;
		}

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		if (engine.isInTransition()) return false;

		// アニメーション終了したらシーン切り替え
		if (!animation_->isPlaying()) {
			engine.changeScene(Epilogue::create(end_type_));
		}

		return false;
	}

	void PlanetPlayer::flashByDamage() {

		// ダメージ後の無敵時間
		if (is_damage_) {
			damage_time_count_ += t2k::Time::getDeltaTime();
			flash_time_count_ += t2k::Time::getDeltaTime();

			// 点滅時間
			const float FLASH_TIME = 0.1f;

			// 点滅処理
			if (FLASH_TIME < flash_time_count_) {
				flash_time_count_ = 0.0f;
				animation_->setRender(animation_->isRender() ^ true);
			}

			// ダメージを受けた後の無敵時間
			const float INVINCIBLE_TIME = 2.0f;

			if (INVINCIBLE_TIME < damage_time_count_) {
				damage_time_count_ = 0.0f;
				flash_time_count_ = 0.0f;
				animation_->setRender(true);
				is_damage_ = false;
			}
		}

	}

}
