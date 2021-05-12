#include <algorithm>
#include "limited_chase_camera2d.h"


namespace spe {

	void LimitedChaseCamera2D::update() {
		// üŒ`•âŠ®
		transform_.position_ += (*chase_position_ - transform_.position_) * lerp_value_;
		// ”ÍˆÍ“à‚Éû‚ß‚é
		transform_.position_.x = std::clamp(transform_.position_.x, top_left_limit_.x, bottom_right_limit_.x);
		transform_.position_.y = std::clamp(transform_.position_.y, top_left_limit_.y, bottom_right_limit_.y);
	}

	LimitedChaseCamera2D::SharedPtr LimitedChaseCamera2D::create(const LimitedChaseCamera2DDesc& desc) {
		LimitedChaseCamera2D::SharedPtr ptr = Camera2D::create<LimitedChaseCamera2D>();
		ptr->chase_position_ = desc.chase_position_;
		ptr->transform_.position_ = *ptr->chase_position_;
		ptr->lerp_value_ = desc.lerp_value_;
		ptr->top_left_limit_ = desc.top_left_limit_;
		ptr->bottom_right_limit_ = desc.bottom_right_limit_;
		return ptr;
	}

}
