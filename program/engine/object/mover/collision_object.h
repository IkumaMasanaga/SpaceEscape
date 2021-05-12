#pragma once
#include "mover.h"


namespace dxe {

	enum class CorrectDirection;
	class CollisionRect;

	// �Փ˔�����Ƃ�N���X
	class CollisionObject : public Mover {
	public:
		using SharedPtr = std::shared_ptr<CollisionObject>;
		using WeakPtr = std::weak_ptr<CollisionObject>;
	private:
		// prev_position_�̍X�V�Ahit���ĂԂ���
		friend class CollisionManager;
		// shared_from_this_constructor���ĂԂ���
		friend class t2k::SharedFactory<Object>;

		//====================================================================================================
		// �����o�ϐ�

		// 1�t���[���O�̃��[���h���W
		t2k::Vector3 prev_position_;

		// �Փ˔����`���X�g
		std::list<std::shared_ptr<CollisionRect>> collision_area_;

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�֐�

		// shared_from_this���g����R���X�g���N�^
		virtual void shared_from_this_constructor() override;

		// �Փˎ��̏���
		virtual void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) {}

		//====================================================================================================
	public:
		CollisionObject() {}
		virtual ~CollisionObject() {}

		//====================================================================================================
		// �����o�֐�

		// �Փ˔����`�̒ǉ�
		void addCollisionRect(const std::string& name, std::shared_ptr<CollisionRect> collision_rect);

		// ���O�ŏՓ˔����`�̎擾
		// ������Ȃ������ꍇ�͋�̃��X�g��Ԃ�
		std::list<std::shared_ptr<CollisionRect>> getCollisionRects(const std::string& name) const;

		//====================================================================================================
	};

}
