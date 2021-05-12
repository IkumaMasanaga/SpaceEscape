#include "planet_plant.h"
#include "../planet_energy_item.h"


namespace spe {

	void PlanetPlant::onCreatedOfEnemy() {

		// 外部CSVファイルから読み込み
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/enemy/plant.csv");
		
		// 色をランダムに決める
		const int COLOR_MAX = 4;
		const int COLOR = rand() % COLOR_MAX;

		animation_->registAnimation("anim", t2k::Texture::createVectorFromFile(data[1+COLOR][0], std::stoi(data[1+COLOR][1]), std::stoi(data[1+COLOR][2]), std::stoi(data[1+COLOR][3]), std::stoi(data[1+COLOR][4]), std::stoi(data[1+COLOR][5])));
		animation_->play("anim", 1.0f, true);

		// 衝突判定矩形の生成
		dxe::CollisionRect::SharedPtr collision = dxe::CollisionRect::create(std::stoi(data[6][1]), std::stoi(data[6][2]), t2k::Vector3(std::stof(data[6][3]), std::stof(data[6][4]), 0));
		collision->is_correct_ = true;
		collision->correct_space_.up_ = 0.0f;
		addCollisionRect("plant", collision);

		// HPの設定
		hp_ = std::stoi(data[7][1]);

		// エフェクト
		std::vector<std::vector<std::string>> effect_data = t2k::loadCsv(data[8][1]);
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

	void PlanetPlant::update() {

	}

	void PlanetPlant::onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

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
						PlanetEnergyItem::create(transform_)->transform_.position_ += t2k::Vector3::UP * 16;
					}
				}
			}
		}

	}

}
