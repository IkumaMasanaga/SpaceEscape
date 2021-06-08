#include "../../physics.h"
#include "../../collision_manager.h"
#include "physics_object.h"


namespace dxe {

	void PhysicsObject::shared_from_this_constructor() {
		// �����Ɠ����Ƀ}�l�[�W���[�ɓo�^
		Physics::getInstance().physics_objects_.emplace_back(std::dynamic_pointer_cast<PhysicsObject>(shared_from_this()));
		CollisionObject::shared_from_this_constructor();
	}

	void PhysicsObject::onCollision(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) {

		// �␳�����Ƃ��̂�
		if (direction != CorrectDirection::NONE) {
			// ���C���ۂ��v�Z
			velocity_ -= ((velocity_ * friction_) * mylib::Time::getDeltaTime());

			// �␳�����ɑ΂��đ��x��ϓ�������
			if (direction == CorrectDirection::UP || direction == CorrectDirection::DOWN) {
				velocity_.y = 0;
			}
			else if (direction == CorrectDirection::LEFT || direction == CorrectDirection::RIGHT) {
				velocity_.x = 0;
			}
		}

		// �h���N���X�̏Փ˔��菈��
		onCollisionOfPhysicsObject(other, rect, direction);
	}

}
