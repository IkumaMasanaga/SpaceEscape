#include "planet_bird.h"
#include "../planet_energy_item.h"


namespace spe {

	void PlanetBird::onCreatedOfEnemy() {

		gravity_scale_ = 0.0f;

		// 外部CSVファイルから読み込み
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/enemy/bird.csv");

		// 色
		const int COLOR_MAX = 4;
		const int COLOR = rand() % COLOR_MAX;
		animation_->registAnimation("bird", t2k::Texture::createVectorFromFile(data[1+COLOR][0], std::stoi(data[1+COLOR][1]), std::stoi(data[1+COLOR][2]), std::stoi(data[1+COLOR][3]), std::stoi(data[1+COLOR][4]), std::stoi(data[1+COLOR][5])));
		animation_->play("bird", 1.0f, true);

		// 衝突判定
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(std::stoi(data[6][1]), std::stoi(data[6][2]), t2k::Vector3(std::stof(data[6][3]), std::stof(data[6][4]), 0.0f));
		rect->is_trigger_ = true;
		addCollisionRect("bird", rect);

		diameter_ = std::stoi(data[8][1]);
		complete_time_ = std::stof(data[9][1]);
		hp_ = std::stoi(data[7][1]);
		
		// エフェクト
		std::vector<std::vector<std::string>> effect_data = t2k::loadCsv(data[10][1]);
		effect_desc_.file_path_ = effect_data[1][0];
		effect_desc_.all_num_ = std::stoi(effect_data[1][1]);
		effect_desc_.x_num_ = std::stoi(effect_data[1][2]);
		effect_desc_.y_num_ = std::stoi(effect_data[1][3]);
		effect_desc_.width_ = std::stoi(effect_data[1][4]);
		effect_desc_.height_ = std::stoi(effect_data[1][5]);
		effect_desc_.alive_time_ = std::stof(effect_data[2][1]);
		effect_desc_.start_alpha_ = std::stof(effect_data[3][1]);
		effect_desc_.complete_alpha_ = std::stof(effect_data[3][1]);

	}

	void PlanetBird::update() {

		if (!init_timer_fluct_) {
			// 回転方向をランダムで設定
			if ((rand() % 2) == 0) {
				sin_y_.setMethodSin(&transform_.position_.y, transform_.position_.y + (diameter_ >> 1), complete_time_);
				cos_x_.setMethodCos(&transform_.position_.x, transform_.position_.x + (diameter_ >> 1), complete_time_);
			}
			else {
				sin_y_.setMethodSin(&transform_.position_.y, transform_.position_.y - (diameter_ >> 1), complete_time_);
				cos_x_.setMethodCos(&transform_.position_.x, transform_.position_.x - (diameter_ >> 1), complete_time_);
			}

			init_timer_fluct_ = true;
		}

		sin_y_.isCompleteUpdate();
		cos_x_.isCompleteUpdate();

	}

	void PlanetBird::onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		// プレイヤーの弾かタックルの矩形と衝突したら
		if (rect->getName() == "bullet" || rect->getName() == "tackle") {
			dxe::SEManager::getInstance().play(dxe::SEKey::HIT);
			// 弾の場合は消す
			if (rect->getName() == "bullet") {
				other->destroyWithChild();
			}

			--hp_;

			// 死亡
			if (hp_ >= 0) {

				destroyWithChild();

				// エフェクトを生成する
				effect_desc_.start_position_ = transform_.position_;
				OneShotAnimation::create(effect_desc_);

				// エネルギー生成数
				const int GENERATE_NUM = t2k::randomRangeI(2, 4);

				// エネルギーを生成
				if (rect->getName() == "bullet") {
					for (int i = 0; i < GENERATE_NUM; ++i) {
						PlanetEnergyItem::create(transform_);
					}
				}
				else {
					for (int i = 0; i < GENERATE_NUM; ++i) {
						// タックルで倒した場合はエネルギーを少し上に生成する
						PlanetEnergyItem::create(transform_)->transform_.position_ += t2k::Vector3::UP * 48;
					}
				}
			}
		}

	}

}
