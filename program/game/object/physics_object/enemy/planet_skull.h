#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetSkull final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetSkull>;
		using WeakPtr = std::weak_ptr<PlanetSkull>;
	private:
		//====================================================================================================
		// メンバ変数

		// 上下移動フラグ true...上下に移動、false...左右に移動
		bool is_move_up_down_ = true;

		// 移動スピード
		float move_power_ = 0;

		// エフェクト
		OneShotAnimation::WeakPtr effect_barrier_;

		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreatedOfEnemy() final override {}

		// 更新
		void update() final override;

		// 衝突時
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		PlanetSkull() {}
		~PlanetSkull() {}

		//====================================================================================================
		// static関数

		// 生成
		static PlanetSkull::SharedPtr create(const bool is_move_up_down);

		//====================================================================================================
	};

}
