#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetBird final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetBird>;
		using WeakPtr = std::weak_ptr<PlanetBird>;
	private:
		//====================================================================================================
		// メンバ変数

		// TimerFluct設定用フラグ
		bool init_timer_fluct_ = false;

		// 直径
		int diameter_ = 0;

		// 完了時間
		float complete_time_ = 0.0f;

		// 2つで円の動きをする

		// y座標の動き
		t2k::TimerFluct<float> sin_y_;

		// x座標の動き
		t2k::TimerFluct<float> cos_x_;

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
		PlanetBird() {}
		~PlanetBird() {}
	};

}
