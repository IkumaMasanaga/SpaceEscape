#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetSlime final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetSlime>;
		using WeakPtr = std::weak_ptr<PlanetSlime>;
	private:
		//====================================================================================================
		// メンバ変数

		// シーケンス最大時間
		float seq_time_max_ = 0.0f;

		// シーケンス最小時間
		float seq_time_min_ = 0.0f;

		// シーケンス切り替え時間
		float seq_change_time_ = 0.0f;

		// 左移動フラグ
		bool is_move_left_ = false;
		
		// 右移動フラグ
		bool is_move_right_ = false;

		// 移動速度
		float move_power_ = 0;

		// 自身の衝突判定矩形
		dxe::CollisionRect::SharedPtr collision_rect_ = nullptr;

		// 待機、移動のシーケンス制御用
		t2k::Sequence<PlanetSlime*> seq_ = t2k::Sequence<PlanetSlime*>(this, &PlanetSlime::seqIdle);

		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreatedOfEnemy() final override;

		// 更新
		void update() final override;

		// 衝突時
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		// 待機シーケンス
		bool seqIdle();

		// 移動シーケンス
		bool seqMove();

		// 左に移動
		void moveLeft();

		// 右に移動
		void moveRight();

		// 移動をやめる
		void moveStop();

		//====================================================================================================
	public:
		PlanetSlime() {}
		~PlanetSlime() {}
	};

}
