#pragma once
#include "vector.h"


namespace t2k {

	class Transform {
	public:
		Transform() {}
		Transform(const t2k::Vector3& position, const float rotation, const float scale) :
			position_(position),
			rotation_(rotation),
			scale_(scale)
		{}

		Vector3 position_ = Vector3::ZERO;
		float rotation_ = 0.0f;
		float scale_ = 1.0f;
	};

}
