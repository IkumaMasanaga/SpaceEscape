#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetFlame final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetFlame>;
		using WeakPtr = std::weak_ptr<PlanetFlame>;
	private:
		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreatedOfEnemy() final override {}

		//====================================================================================================
	public:
		PlanetFlame() {}
		~PlanetFlame() {}

		//====================================================================================================
		// static関数

		// 生成
		static PlanetFlame::SharedPtr create(const int map_width, const int map_height);

		//====================================================================================================
	};

}
