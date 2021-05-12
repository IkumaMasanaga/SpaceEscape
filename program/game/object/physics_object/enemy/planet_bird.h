#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetBird final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetBird>;
		using WeakPtr = std::weak_ptr<PlanetBird>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// TimerFluct�ݒ�p�t���O
		bool init_timer_fluct_ = false;

		// ���a
		int diameter_ = 0;

		// ��������
		float complete_time_ = 0.0f;

		// 2�ŉ~�̓���������

		// y���W�̓���
		t2k::TimerFluct<float> sin_y_;

		// x���W�̓���
		t2k::TimerFluct<float> cos_x_;

		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreatedOfEnemy() final override;

		// �X�V
		void update() final override;

		// �Փˎ�
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		PlanetBird() {}
		~PlanetBird() {}
	};

}
