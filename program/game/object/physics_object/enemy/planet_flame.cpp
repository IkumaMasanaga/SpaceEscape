#include "planet_flame.h"
#include "../../../player_status.h"
#include "../../../save_data.h"


namespace spe {

	PlanetFlame::SharedPtr PlanetFlame::create(const int map_width, const int map_height) {

		PlanetFlame::SharedPtr ptr = PlanetEnemy::create<PlanetFlame>();
		ptr->gravity_scale_ = 0.0f;

		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/enemy/flame.csv");

		// アニメーション
		ptr->animation_->registAnimation("flame", t2k::Texture::createVectorFromFile(data[1][0], std::stoi(data[1][1]), std::stoi(data[1][2]), std::stoi(data[1][3]), std::stoi(data[1][4]), std::stoi(data[1][5])));
		ptr->animation_->alpha_ = std::stof(data[2][1]);
		ptr->animation_->play("flame", std::stof(data[3][1]), true);
		ptr->animation_->transform_.scale_ = std::stof(data[4][1]);

		ptr->animation_->render_position_from_camera_ = 0.0f;

		// 海王星のアイテムを持っている場合はアルファ値を下げる
		if (PlayerStatus::getInstance().hasItem(PlanetID::NEPTUNE)) {
			ptr->animation_->alpha_ *= 0.5f;
		}
		// マップの幅分の当たり判定を作る
		else {
			dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(map_width, (int)(map_height * 0.8f));
			rect->is_trigger_ = true;
			ptr->addCollisionRect("flame", rect);
		}

		return ptr;

	}

}
