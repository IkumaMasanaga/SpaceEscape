#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class PlanetPlayerBullet final : public dxe::CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetPlayerBullet>;
		using WeakPtr = std::weak_ptr<PlanetPlayerBullet>;
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
		PlanetPlayerBullet() {}
		~PlanetPlayerBullet() {}

		//====================================================================================================
		// static�֐�

		static PlanetPlayerBullet::SharedPtr create(const t2k::Vector3& direction, const t2k::Transform& transform);

		//====================================================================================================
	};

}
