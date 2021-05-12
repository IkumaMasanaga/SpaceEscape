#include "../dx_engine.h"
#include "../scene.h"
#include "object.h"


namespace dxe {

	void Object::shared_from_this_constructor() {
		// “o˜^
		DxEngine::getInstance().getNowScene()->updates_.emplace_back(shared_from_this());
		onCreated();
	}

}
