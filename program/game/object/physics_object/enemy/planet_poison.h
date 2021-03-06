#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetPoison final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetPoison>;
		using WeakPtr = std::weak_ptr<PlanetPoison>;
	private:
		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreatedOfEnemy() final override {}

		//====================================================================================================
	public:
		PlanetPoison() {}
		~PlanetPoison() {}

		//====================================================================================================
		// static関数

		// 生成
		static PlanetPoison::SharedPtr create(const int map_width, const int map_height);

		//====================================================================================================
	};

}
