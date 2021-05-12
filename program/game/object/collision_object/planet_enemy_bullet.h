#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class PlanetEnemyBullet final : public dxe::CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetEnemyBullet>;
		using WeakPtr = std::weak_ptr<PlanetEnemyBullet>;
	private:
		//====================================================================================================
		// メンバ変数

		// 打ち出された方向ベクトル
		t2k::Vector3 direction_;

		// 弾の速度
		float speed_ = 0.0f;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update() final override;

		// 衝突時
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		PlanetEnemyBullet() {}
		~PlanetEnemyBullet() {}

		//====================================================================================================
		// static関数

		static PlanetEnemyBullet::SharedPtr create(const t2k::Vector3& direction, const float speed, const t2k::Transform& transform);

		//====================================================================================================
	};

}
