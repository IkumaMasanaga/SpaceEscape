#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetPlant final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetPlant>;
		using WeakPtr = std::weak_ptr<PlanetPlant>;
	private:
		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreatedOfEnemy() final override;

		// 更新
		void update() final override;

		// 衝突時
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		PlanetPlant() {}
		~PlanetPlant() {}
	};

}
