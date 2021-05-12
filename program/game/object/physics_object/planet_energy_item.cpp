#include "planet_energy_item.h"


namespace spe {

	PlanetEnergyItem::SharedPtr PlanetEnergyItem::create(const t2k::Transform& transform) {
		
		PlanetEnergyItem::SharedPtr ptr = dxe::PhysicsObject::create<PlanetEnergyItem>();
		ptr->setName("energy_item");

		// 外部CSVファイルから読み込み
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/energy_item.csv");

		// アニメーション
		dxe::AnimationSprite::SharedPtr anim = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		anim->registAnimation("energy_item", t2k::Texture::createVectorFromFile(data[0][1], std::stoi(data[0][2]), std::stoi(data[0][3]), std::stoi(data[0][4]), std::stoi(data[0][5]), std::stoi(data[0][6])));
		anim->play("energy_item", std::stof(data[3][1]), true);
		ptr->pushChild(anim);

		// 衝突判定矩形
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(std::stoi(data[1][1]), std::stoi(data[1][2]), t2k::Vector3(std::stof(data[2][1]), std::stof(data[2][2]), std::stof(data[2][3])));
		rect->is_correct_ = true;
		ptr->addCollisionRect("energy_item", rect);

		// 抵抗値の設定
		ptr->friction_ = t2k::Vector3::ZERO;
		ptr->drag_ = t2k::Vector3(std::stof(data[4][1]), std::stof(data[4][2]), std::stof(data[4][3]));
		ptr->gravity_scale_ = std::stof(data[7][1]);

		// 飛び出しベクトルの設定
		t2k::Vector3 pop_out;
		pop_out.x = t2k::randomRangeF(std::stof(data[5][1]), std::stof(data[6][1]));
		pop_out.y = t2k::randomRangeF(std::stof(data[5][2]), std::stof(data[6][2]));
		ptr->addForceFrame(pop_out);

		ptr->transform_ = transform;

		return ptr;

	}

}
