#include "../../../dx_engine.h"
#include "../../../scene.h"
#include "render_object.h"


namespace dxe {

	void RenderObject::shared_from_this_constructor() {
		// 生成と同時にマネージャーに登録
		DxEngine::getInstance().getNowScene()->renders_.emplace_back(std::dynamic_pointer_cast<RenderObject>(shared_from_this()));
		Object::shared_from_this_constructor();
	}

	void RenderObject::setBlendMode() const {

		switch (blend_mode_) {
		case BlendMode::ALPHA:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(alpha_ * 255));
			break;
		case BlendMode::ADD:
			SetDrawBlendMode(DX_BLENDMODE_ADD, (int)(alpha_ * 255));
			break;
		case BlendMode::SUB:
			SetDrawBlendMode(DX_BLENDMODE_SUB, (int)(alpha_ * 255));
			break;
		case BlendMode::MUL:
			SetDrawBlendMode(DX_BLENDMODE_MUL, (int)(alpha_ * 255));
			break;
		}

	}

}
