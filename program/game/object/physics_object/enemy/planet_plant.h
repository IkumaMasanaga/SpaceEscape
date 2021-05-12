#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetPlant final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetPlant>;
		using WeakPtr = std::weak_ptr<PlanetPlant>;
	private:
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
		PlanetPlant() {}
		~PlanetPlant() {}
	};

}
