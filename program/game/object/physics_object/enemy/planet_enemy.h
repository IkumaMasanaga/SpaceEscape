#pragma once
#include "../../../../engine/dxe.h"
#include "../../mover/one_shot_animation.h"


namespace spe {

	class PlanetEnemy : public dxe::PhysicsObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetEnemy>;
		using WeakPtr = std::weak_ptr<PlanetEnemy>;
	private:
		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreated() final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// メンバ変数

		// 画像
		dxe::AnimationSprite::SharedPtr animation_ = nullptr;

		// HP
		int hp_ = 0;

		// 攻撃を受けた時のエフェクト生成構造体
		OneShotAnimationDesc effect_desc_;

		//====================================================================================================
		// メンバ関数

		// 派生先の生成時
		virtual void onCreatedOfEnemy() = 0;

		// 更新
		virtual void update() override {}

		// 衝突時
		virtual void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) override {}

		//====================================================================================================
	public:
		PlanetEnemy() {}
		virtual ~PlanetEnemy() {}
	};

}
