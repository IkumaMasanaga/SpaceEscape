#include "../../collision_manager.h"
#include "../collision_rect.h"
#include "collision_object.h"


namespace dxe {

	void CollisionObject::shared_from_this_constructor() {
		// 生成と同時にマネージャーに登録
		CollisionManager::getInstance().collision_objects_.emplace_back(std::dynamic_pointer_cast<CollisionObject>(shared_from_this()));
		Object::shared_from_this_constructor();
	}

	void CollisionObject::addCollisionRect(const std::string& name, std::shared_ptr<CollisionRect> collision_rect) {
		collision_rect->setName(name);
		collision_area_.emplace_back(collision_rect);
	}

	std::list<std::shared_ptr<CollisionRect>> CollisionObject::getCollisionRects(const std::string& name) const {
		std::list<std::shared_ptr<CollisionRect>> ret;
		for (const auto& rect : collision_area_) {
			// 名前が合わなければ次へ
			if (rect->getName() != name) continue;
			ret.emplace_back(rect);
		}
		return ret;
	}

}
