#include "planet_enemy_bullet.h"
#include "../render_object/planet_map.h"


namespace spe {

	void PlanetEnemyBullet::update() {
		// 方向に速度分進める
		transform_.position_ += (direction_ * speed_);

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		const int WINDOW_TOP = -(engine.getWindowWidth() >> 1);
		const int WINDOW_BOTTOM = (engine.getWindowWidth() >> 1);

		// ウィンドウの上下に行ったら消す
		if (transform_.position_.y < WINDOW_TOP ||
			WINDOW_BOTTOM < transform_.position_.y) {
			destroyWithChild();
		}

	}

	void PlanetEnemyBullet::onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		// マップかタックルと当たったら消える
		if (rect->getName() != "map" || rect->getName() != "tackle") return;
		destroyWithChild();

	}

	PlanetEnemyBullet::SharedPtr PlanetEnemyBullet::create(const t2k::Vector3& direction, const float speed, const t2k::Transform& transform) {

		PlanetEnemyBullet::SharedPtr ptr = CollisionObject::create<PlanetEnemyBullet>();

		ptr->setName("enemy");

		// 速度の設定
		ptr->speed_ = speed;

		// 外部CSVファイルから読み込み
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/enemy/enemy_bullet.csv");

		// 方向の設定と正規化
		ptr->direction_ = direction;
		ptr->direction_.normalize();

		// アニメーション画像
		dxe::AnimationSprite::SharedPtr anim = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		anim->registAnimation("bullet", t2k::Texture::createVectorFromFile(data[0][1], std::stoi(data[0][2]), std::stoi(data[0][3]), std::stoi(data[0][4]), std::stoi(data[0][5]), std::stoi(data[0][6])));
		anim->play("bullet", std::stof(data[3][1]), true);
		ptr->pushChild(anim);

		// 衝突判定矩形
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(std::stoi(data[1][1]), std::stoi(data[1][2]), t2k::Vector3(std::stof(data[2][1]), std::stof(data[2][2]), std::stof(data[2][3])));
		rect->is_trigger_ = true;
		ptr->addCollisionRect("enemy_bullet", rect);
		ptr->transform_ = transform;

		return ptr;
	}

}
