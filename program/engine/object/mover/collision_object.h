#pragma once
#include "mover.h"


namespace dxe {

	enum class CorrectDirection;
	class CollisionRect;

	// 衝突判定をとるクラス
	class CollisionObject : public Mover {
	public:
		using SharedPtr = std::shared_ptr<CollisionObject>;
		using WeakPtr = std::weak_ptr<CollisionObject>;
	private:
		// prev_position_の更新、hitを呼ぶため
		friend class CollisionManager;
		// shared_from_this_constructorを呼ぶため
		friend class t2k::SharedFactory<Object>;

		//====================================================================================================
		// メンバ変数

		// 1フレーム前のワールド座標
		t2k::Vector3 prev_position_;

		// 衝突判定矩形リスト
		std::list<std::shared_ptr<CollisionRect>> collision_area_;

		//====================================================================================================
	protected:
		//====================================================================================================
		// メンバ関数

		// shared_from_thisが使えるコンストラクタ
		virtual void shared_from_this_constructor() override;

		// 衝突時の処理
		virtual void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) {}

		//====================================================================================================
	public:
		CollisionObject() {}
		virtual ~CollisionObject() {}

		//====================================================================================================
		// メンバ関数

		// 衝突判定矩形の追加
		void addCollisionRect(const std::string& name, std::shared_ptr<CollisionRect> collision_rect);

		// 名前で衝突判定矩形の取得
		// 見つからなかった場合は空のリストを返す
		std::list<std::shared_ptr<CollisionRect>> getCollisionRects(const std::string& name) const;

		//====================================================================================================
	};

}
