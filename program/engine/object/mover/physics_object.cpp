#include "../../physics.h"
#include "../../collision_manager.h"
#include "physics_object.h"


namespace dxe {

	void PhysicsObject::shared_from_this_constructor() {
		// 生成と同時にマネージャーに登録
		Physics::getInstance().physics_objects_.emplace_back(std::dynamic_pointer_cast<PhysicsObject>(shared_from_this()));
		CollisionObject::shared_from_this_constructor();
	}

	void PhysicsObject::onCollision(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) {

		// 補正したときのみ
		if (direction != CorrectDirection::NONE) {
			// 摩擦っぽい計算
			velocity_ -= ((velocity_ * friction_) * mylib::Time::getDeltaTime());

			// 補正方向に対して速度を変動させる
			if (direction == CorrectDirection::UP || direction == CorrectDirection::DOWN) {
				velocity_.y = 0;
			}
			else if (direction == CorrectDirection::LEFT || direction == CorrectDirection::RIGHT) {
				velocity_.x = 0;
			}
		}

		// 派生クラスの衝突判定処理
		onCollisionOfPhysicsObject(other, rect, direction);
	}

}
