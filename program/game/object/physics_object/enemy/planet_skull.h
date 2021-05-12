#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetSkull final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetSkull>;
		using WeakPtr = std::weak_ptr<PlanetSkull>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �㉺�ړ��t���O true...�㉺�Ɉړ��Afalse...���E�Ɉړ�
		bool is_move_up_down_ = true;

		// �ړ��X�s�[�h
		float move_power_ = 0;

		// �G�t�F�N�g
		OneShotAnimation::WeakPtr effect_barrier_;

		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreatedOfEnemy() final override {}

		// �X�V
		void update() final override;

		// �Փˎ�
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		PlanetSkull() {}
		~PlanetSkull() {}

		//====================================================================================================
		// static�֐�

		// ����
		static PlanetSkull::SharedPtr create(const bool is_move_up_down);

		//====================================================================================================
	};

}
