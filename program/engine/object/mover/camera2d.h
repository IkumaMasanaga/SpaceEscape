#pragma once
#include "mover.h"


namespace dxe {

	class Camera2D : public Mover {
	public:
		using SharedPtr = std::shared_ptr<Camera2D>;
		using WeakPtr = std::weak_ptr<Camera2D>;
	private:


	public:
		Camera2D() {}
		~Camera2D() {}

		//====================================================================================================
		// ƒƒ“ƒo•Ï”

		// •`‰æŠ„‡
		float render_scale_ = 1.0f;

		//====================================================================================================
	};

}
