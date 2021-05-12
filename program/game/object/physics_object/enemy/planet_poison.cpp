#include "planet_poison.h"
#include "../../../player_status.h"
#include "../../../save_data.h"


namespace spe {

	PlanetPoison::SharedPtr PlanetPoison::create(const int map_width, const int map_height) {

		PlanetPoison::SharedPtr ptr = PlanetEnemy::create<PlanetPoison>();
		ptr->gravity_scale_ = 0.0f;

		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/enemy/poison.csv");

		// アニメーション
		ptr->animation_->registAnimation("poison", t2k::Texture::createVectorFromFile(data[1][0], std::stoi(data[1][1]), std::stoi(data[1][2]), std::stoi(data[1][3]), std::stoi(data[1][4]), std::stoi(data[1][5])));
		ptr->animation_->alpha_ = std::stof(data[2][1]);
		ptr->animation_->play("poison", std::stof(data[3][1]), true);
		ptr->animation_->transform_.scale_ = std::stof(data[4][1]);

		ptr->animation_->render_position_from_camera_ = 0.0f;

		// 木星のアイテムを持っている場合はアルファ値を下げる
		if (PlayerStatus::getInstance().hasItem(PlanetID::JUPITER)) {
			ptr->animation_->alpha_ *= 0.5f;
		}
		// マップの幅分の当たり判定を作る
		else {
			dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(map_width, (int)(map_height * 0.7f));
			rect->is_trigger_ = true;
			ptr->addCollisionRect("poison", rect);
		}

		return ptr;

	}

}
