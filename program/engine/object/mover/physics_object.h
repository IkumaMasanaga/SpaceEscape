#pragma once
#include "collision_object.h"


namespace dxe {

	// 物理演算の影響を受けるクラス
	// 重力、空気抵抗、摩擦
	class PhysicsObject : public CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<PhysicsObject>;
		using WeakPtr = std::weak_ptr<PhysicsObject>;
	private:
		// shared_from_this_constructorを呼ぶため
		friend class t2k::SharedFactory<Object>;

		//====================================================================================================
		// メンバ変数

		// 速さ
		t2k::Vector3 velocity_ = t2k::Vector3::ZERO;

		//====================================================================================================
		// メンバ関数

		// 衝突時の処理
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// メンバ関数

		// shared_from_thisが使えるコンストラクタ
		virtual void shared_from_this_constructor() override;

		// 衝突時の派生クラスの処理
		// このクラスの派生クラス固有の衝突時の振る舞いをしたいときはこの関数を実装する
		virtual void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) {}

		//====================================================================================================
	public:
		PhysicsObject() {}
		virtual ~PhysicsObject() {}

		//====================================================================================================
		// メンバ変数

		// 速度（参照用）
		const t2k::Vector3& VELOCITY = velocity_;

		// 空気抵抗っぽい値
		// 実際には時間単位でvelocity_を減少させる割合
		t2k::Vector3 drag_ = t2k::Vector3(1.0f, 0.0f, 0.0f);

		// 摩擦っぽい値
		// 実際には時間単位で座標補正時にvelocity_を減少させる割合
		t2k::Vector3 friction_ = t2k::Vector3(10.0f, 10.0f, 0.0f);

		// 重力の影響割合
		float gravity_scale_ = 1.0f;

		//====================================================================================================
		// メンバ関数

		// 速度に直接力を加える（時間単位）
		inline void addForceTime(const t2k::Vector3& force) { velocity_ += (force * t2k::Time::getDeltaTime()); }

		// 速度に直接力を加える（フレーム単位）
		inline void addForceFrame(const t2k::Vector3& force) { velocity_ += force; }

		//====================================================================================================
	};

}
