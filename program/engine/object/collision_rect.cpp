#include "collision_rect.h"


namespace dxe {

	CollisionRect::SharedPtr CollisionRect::create(const int width, const int height, const t2k::Vector3& center) {
		CollisionRect::SharedPtr ptr = Object::create<CollisionRect>();
		ptr->width_ = width;
		ptr->height_ = height;
		ptr->center_ = center;
		return ptr;
	}

}
