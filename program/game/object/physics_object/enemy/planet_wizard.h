#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetWizard final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetWizard>;
		using WeakPtr = std::weak_ptr<PlanetWizard>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// y���W�̓���
		t2k::TimerFluct<float> sin_y_;

		// �e���ˊԊu
		float shot_time_ = 0.0f;

		// �e�̑��x
		float shot_speed_ = 0.0f;

		// �ҋ@�A�ړ��̃V�[�P���X����p
		t2k::Sequence<PlanetWizard*> seq_ = t2k::Sequence<PlanetWizard*>(this, &PlanetWizard::seqInit);

		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreatedOfEnemy() final override;

		// �X�V
		void update() final override;

		// �Փˎ�
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		// ������
		bool seqInit();

		// �ҋ@
		bool seqIdle();

		// �U��
		bool seqAttack();

		//====================================================================================================
	public:
		PlanetWizard() {}
		~PlanetWizard() {}
	};

}
