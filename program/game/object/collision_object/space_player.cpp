#include <algorithm>
#include "space_player.h"
#include "../mover/one_shot_animation.h"
#include "../../player_status.h"
#include "../../save_data.h"


namespace spe {

	void SpacePlayer::onCreated() {

		// 外部CSVファイルから読み込み
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/space/player.csv");

		// 速度
		speed_max_ = std::stof(data[2][1]);

		// エネルギー消費割合
		consume_energy_rate_ = std::stof(data[3][1]);

		// 画像
		std::vector<std::vector<std::string>> graphics_data = t2k::loadCsv(data[0][1]);
		for (int i = 0; i < TEXTURE_NUM; ++i) {
			textures_[i] = t2k::Texture::createFromFile(graphics_data[i][1]);
		}

		sprite_ = dxe::Sprite::createFromTexture(textures_[TEXTURE_INDEX_NORMAL]);
		pushChild(sprite_);
		sprite_->render_priority_ = 1.0f;

		// 衝突判定
		dxe::CollisionRect::SharedPtr collision_rect = dxe::CollisionRect::create(std::stoi(data[4][1]), std::stoi(data[4][2]), t2k::Vector3(std::stof(data[4][3]), std::stof(data[4][4]), 0.0f));
		collision_rect->is_correct_ = true;
		addCollisionRect("player", collision_rect);

		y_.setCondition(&up_, &down_);
		x_.setCondition(&left_, &right_);

		// 感度
		const float SENSITIVITY = std::stof(data[1][1]);
		y_.setIPS(SENSITIVITY);
		x_.setIPS(SENSITIVITY);

		// ジェット生成間隔を金星のアイテム獲得状況によって変える
		generate_jet_time_ = (PlayerStatus::getInstance().hasItem(PlanetID::VENUS)) ? generate_jet_time_ * 2 : generate_jet_time_;

		// ジェット生成構造体の初期化
		std::vector<std::vector<std::string>> jet_data = t2k::loadCsv("data/scene/space/player_jet.csv");
		jet_desc_.file_path_ = jet_data[1][0];
		jet_desc_.all_num_ = std::stoi(jet_data[1][1]);
		jet_desc_.x_num_ = std::stoi(jet_data[1][2]);
		jet_desc_.y_num_ = std::stoi(jet_data[1][3]);
		jet_desc_.width_ = std::stoi(jet_data[1][4]);
		jet_desc_.height_ = std::stoi(jet_data[1][5]);
		jet_desc_.start_scale_ = std::stof(jet_data[2][1]);
		jet_desc_.complete_scale_ = std::stof(jet_data[3][1]);
		jet_desc_.start_alpha_= std::stof(jet_data[4][1]);
		jet_desc_.complete_alpha_= std::stof(jet_data[5][1]);
		jet_desc_.alive_time_ = std::stof(jet_data[6][1]);

	}

	void SpacePlayer::update() {

		PlayerStatus& status = PlayerStatus::getInstance();

		x_.update();
		y_.update();

		// エネルギーがないと動かない
		if (0 < status.getEnergy()) {

			// 各種入力受け取り
			up_ = t2k::Input::isKeyDown(t2k::Input::KEYBORD_UP);
			down_ = t2k::Input::isKeyDown(t2k::Input::KEYBORD_DOWN);
			left_ = t2k::Input::isKeyDown(t2k::Input::KEYBORD_LEFT);
			right_ = t2k::Input::isKeyDown(t2k::Input::KEYBORD_RIGHT);

			// ジョイパッド
			mylib::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
			if (joypad) {
				up_ |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_DPAD_UP) || joypad->isPressLeftThumbUpTrigger();
				down_ |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_DPAD_DOWN) || joypad->isPressLeftThumbDownTrigger();
				left_ |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_DPAD_LEFT) || joypad->isPressLeftThumbLeftTrigger();
				right_ |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_DPAD_RIGHT) || joypad->isPressLeftThumbRightTrigger();
			}

		}
		// 入力を消す
		else {
			up_ = down_ = left_ = right_ = false;
		}

		// 描画テクスチャ要素
		int index = 0;
		// 上下の入力によって要素数を変更する
		if (up_) index += TEXTURE_INDEX_UP;
		if (down_) index += TEXTURE_INDEX_DOWN;

		// 左右の向きを切り替える
		// 同時押し時は先に入力されていた方に向く
		if (left_ && !right_) {
			sprite_->is_flip_y_ = true;
		}
		if (!left_ && right_) {
			sprite_->is_flip_y_ = false;
		}

		// 描画テクスチャ変更
		sprite_->changeTexture(textures_[index % TEXTURE_NUM]);

		// 移動
		float x = x_.getValue();
		float y = y_.getValue();

		// 斜め入力でも最高速度を超えないようにする
		float speed = std::clamp(sqrt(x * x + y * y) * speed_max_, 0.0f, speed_max_);

		// 移動ベクトルの生成と正規化
		t2k::Vector3 move = t2k::Vector3(x, y, 0);
		move.normalize();

		// 金星のアイテムを持っていれば減少割合を軽減する
		status.changeEnergy(-speed * consume_energy_rate_ * (status.hasItem(PlanetID::VENUS) ? 0.7f : 1.0f));

		// 移動
		transform_.position_ += (move * speed);

		// ジェット生成
		generate_jet_time_count_ += mylib::Time::getDeltaTime();
		if (0 < speed && (generate_jet_time_ * (speed_max_ / speed)) < generate_jet_time_count_) {
			dxe::SEManager::getInstance().play(dxe::SEKey::JET);
			generate_jet_time_count_ = 0.0f;
			jet_desc_.start_position_ = transform_.position_;
			OneShotAnimation::create(jet_desc_);
		}

		// エネルギーが0かつ動いていなければゲームオーバー
		if (speed == 0 && status.getEnergy() <= 0) {
			is_dead_ = true;
		}
	}

	void SpacePlayer::onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		// 衝突した方向によって速度をリセットする
		switch (direction) {
		case dxe::CorrectDirection::NONE: return;
		case dxe::CorrectDirection::UP:
		case dxe::CorrectDirection::DOWN:
			y_.resetValue();
			break;
		case dxe::CorrectDirection::LEFT:
		case dxe::CorrectDirection::RIGHT:
			x_.resetValue();
			break;
		}

	}

}
