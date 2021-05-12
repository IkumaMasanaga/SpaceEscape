#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class PlanetEnergyItem final : public dxe::PhysicsObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetEnergyItem>;
		using WeakPtr = std::weak_ptr<PlanetEnergyItem>;
	private:


	public:
		PlanetEnergyItem() {}
		~PlanetEnergyItem() {}

		//====================================================================================================
		// staticä÷êî

		// ê∂ê¨
		static PlanetEnergyItem::SharedPtr create(const t2k::Transform& transform);

		//====================================================================================================
	};

}
