#pragma once
#include "../library/t2klib.h"


namespace dxe {

	// �������Z�N���X
	// �������ꂽPhysicsObject�͎����I�ɂ��̃N���X�ɓo�^����܂�
	// �������Z�������s
	// �d�͂̐ݒ�
	class Physics final : public mylib::Singleton<Physics> {
	private:
		// ���N���X�Ő������邽��
		friend class mylib::Singleton<Physics>;
		// update���ĂԂ���
		friend class Scene;
		// �����ƂƂ���physics_objects_�ɓo�^���邽��
		friend class PhysicsObject;

		Physics() {}

		//====================================================================================================
		// �����o�ϐ�

		// PhysicsObject�ꊇ�Ǘ��p���X�g
		std::list<std::shared_ptr<PhysicsObject>> physics_objects_;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		// �������Z�������s
		void update();

		//====================================================================================================
	public:
		~Physics() {}

		//====================================================================================================
		// �����o�ϐ�

		// �d��
		t2k::Vector3 gravity_ = t2k::Vector3(0.0f, 9.81f, 0.0f);

		//====================================================================================================
	};

}
