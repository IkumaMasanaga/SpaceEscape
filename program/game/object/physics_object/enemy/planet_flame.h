#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetFlame final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetFlame>;
		using WeakPtr = std::weak_ptr<PlanetFlame>;
	private:
		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreatedOfEnemy() final override {}

		//====================================================================================================
	public:
		PlanetFlame() {}
		~PlanetFlame() {}

		//====================================================================================================
		// static�֐�

		// ����
		static PlanetFlame::SharedPtr create(const int map_width, const int map_height);

		//====================================================================================================
	};

}
