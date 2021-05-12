#include "physics.h"
#include "object/mover/physics_object.h"


namespace dxe {

	void Physics::update() {

		// 更新優先度の小さい順にリストを並び替える
		physics_objects_.sort([](const Object::SharedPtr left, const Object::SharedPtr right) {
			return left->update_priority_ < right->update_priority_;
		});

		std::list<std::shared_ptr<PhysicsObject>>::iterator it = physics_objects_.begin();

		// 登録されているすべてのobjectについて
		while (it != physics_objects_.end()) {
			// 生死判定
			if (!(*it)->isAlive()) {
				it = physics_objects_.erase(it);
				continue;
			}
			// 有効判定
			if ((*it)->isActive()) {
				// 速度に重力を足す
				(*it)->addForceTime(gravity_ * (*it)->gravity_scale_);
				// 空気抵抗
				(*it)->addForceTime(-((*it)->VELOCITY * (*it)->drag_));
				// 座標に速度を足す
				(*it)->transform_.position_ += (*it)->toLocalPosition((*it)->VELOCITY);
			}
			++it;
		}

	}

}
