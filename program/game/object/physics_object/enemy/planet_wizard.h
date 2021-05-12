#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetWizard final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetWizard>;
		using WeakPtr = std::weak_ptr<PlanetWizard>;
	private:
		//====================================================================================================
		// メンバ変数

		// y座標の動き
		t2k::TimerFluct<float> sin_y_;

		// 弾発射間隔
		float shot_time_ = 0.0f;

		// 弾の速度
		float shot_speed_ = 0.0f;

		// 待機、移動のシーケンス制御用
		t2k::Sequence<PlanetWizard*> seq_ = t2k::Sequence<PlanetWizard*>(this, &PlanetWizard::seqInit);

		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreatedOfEnemy() final override;

		// 更新
		void update() final override;

		// 衝突時
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		// 初期化
		bool seqInit();

		// 待機
		bool seqIdle();

		// 攻撃
		bool seqAttack();

		//====================================================================================================
	public:
		PlanetWizard() {}
		~PlanetWizard() {}
	};

}
