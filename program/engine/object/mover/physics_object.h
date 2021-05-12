#pragma once
#include "collision_object.h"


namespace dxe {

	// �������Z�̉e�����󂯂�N���X
	// �d�́A��C��R�A���C
	class PhysicsObject : public CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<PhysicsObject>;
		using WeakPtr = std::weak_ptr<PhysicsObject>;
	private:
		// shared_from_this_constructor���ĂԂ���
		friend class t2k::SharedFactory<Object>;

		//====================================================================================================
		// �����o�ϐ�

		// ����
		t2k::Vector3 velocity_ = t2k::Vector3::ZERO;

		//====================================================================================================
		// �����o�֐�

		// �Փˎ��̏���
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�֐�

		// shared_from_this���g����R���X�g���N�^
		virtual void shared_from_this_constructor() override;

		// �Փˎ��̔h���N���X�̏���
		// ���̃N���X�̔h���N���X�ŗL�̏Փˎ��̐U�镑�����������Ƃ��͂��̊֐�����������
		virtual void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<CollisionRect> rect, const CorrectDirection direction) {}

		//====================================================================================================
	public:
		PhysicsObject() {}
		virtual ~PhysicsObject() {}

		//====================================================================================================
		// �����o�ϐ�

		// ���x�i�Q�Ɨp�j
		const t2k::Vector3& VELOCITY = velocity_;

		// ��C��R���ۂ��l
		// ���ۂɂ͎��ԒP�ʂ�velocity_�����������銄��
		t2k::Vector3 drag_ = t2k::Vector3(1.0f, 0.0f, 0.0f);

		// ���C���ۂ��l
		// ���ۂɂ͎��ԒP�ʂō��W�␳����velocity_�����������銄��
		t2k::Vector3 friction_ = t2k::Vector3(10.0f, 10.0f, 0.0f);

		// �d�͂̉e������
		float gravity_scale_ = 1.0f;

		//====================================================================================================
		// �����o�֐�

		// ���x�ɒ��ڗ͂�������i���ԒP�ʁj
		inline void addForceTime(const t2k::Vector3& force) { velocity_ += (force * t2k::Time::getDeltaTime()); }

		// ���x�ɒ��ڗ͂�������i�t���[���P�ʁj
		inline void addForceFrame(const t2k::Vector3& force) { velocity_ += force; }

		//====================================================================================================
	};

}
