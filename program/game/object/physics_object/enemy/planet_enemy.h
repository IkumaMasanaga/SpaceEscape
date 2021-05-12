#pragma once
#include "../../../../engine/dxe.h"
#include "../../mover/one_shot_animation.h"


namespace spe {

	class PlanetEnemy : public dxe::PhysicsObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetEnemy>;
		using WeakPtr = std::weak_ptr<PlanetEnemy>;
	private:
		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreated() final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�ϐ�

		// �摜
		dxe::AnimationSprite::SharedPtr animation_ = nullptr;

		// HP
		int hp_ = 0;

		// �U�����󂯂����̃G�t�F�N�g�����\����
		OneShotAnimationDesc effect_desc_;

		//====================================================================================================
		// �����o�֐�

		// �h����̐�����
		virtual void onCreatedOfEnemy() = 0;

		// �X�V
		virtual void update() override {}

		// �Փˎ�
		virtual void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) override {}

		//====================================================================================================
	public:
		PlanetEnemy() {}
		virtual ~PlanetEnemy() {}
	};

}
