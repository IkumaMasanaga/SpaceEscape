#include "physics.h"
#include "object/mover/physics_object.h"


namespace dxe {

	void Physics::update() {

		// �X�V�D��x�̏��������Ƀ��X�g����ёւ���
		physics_objects_.sort([](const Object::SharedPtr left, const Object::SharedPtr right) {
			return left->update_priority_ < right->update_priority_;
		});

		std::list<std::shared_ptr<PhysicsObject>>::iterator it = physics_objects_.begin();

		// �o�^����Ă��邷�ׂĂ�object�ɂ���
		while (it != physics_objects_.end()) {
			// ��������
			if (!(*it)->isAlive()) {
				it = physics_objects_.erase(it);
				continue;
			}
			// �L������
			if ((*it)->isActive()) {
				// ���x�ɏd�͂𑫂�
				(*it)->addForceTime(gravity_ * (*it)->gravity_scale_);
				// ��C��R
				(*it)->addForceTime(-((*it)->VELOCITY * (*it)->drag_));
				// ���W�ɑ��x�𑫂�
				(*it)->transform_.position_ += (*it)->toLocalPosition((*it)->VELOCITY);
			}
			++it;
		}

	}

}
