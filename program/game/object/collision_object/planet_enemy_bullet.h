#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class PlanetEnemyBullet final : public dxe::CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetEnemyBullet>;
		using WeakPtr = std::weak_ptr<PlanetEnemyBullet>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �ł��o���ꂽ�����x�N�g��
		t2k::Vector3 direction_;

		// �e�̑��x
		float speed_ = 0.0f;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update() final override;

		// �Փˎ�
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		PlanetEnemyBullet() {}
		~PlanetEnemyBullet() {}

		//====================================================================================================
		// static�֐�

		static PlanetEnemyBullet::SharedPtr create(const t2k::Vector3& direction, const float speed, const t2k::Transform& transform);

		//====================================================================================================
	};

}
