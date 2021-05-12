#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetPoison final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetPoison>;
		using WeakPtr = std::weak_ptr<PlanetPoison>;
	private:
		//====================================================================================================
		// ÉÅÉìÉoä÷êî

		// ê∂ê¨éû
		void onCreatedOfEnemy() final override {}

		//====================================================================================================
	public:
		PlanetPoison() {}
		~PlanetPoison() {}

		//====================================================================================================
		// staticä÷êî

		// ê∂ê¨
		static PlanetPoison::SharedPtr create(const int map_width, const int map_height);

		//====================================================================================================
	};

}
