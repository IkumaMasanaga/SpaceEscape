#include "planet_key_item_frame.h"
#include "ui_frame.h"


namespace spe {

	void PlanetKeyItemFrame::update() {

		// 枠が有効な場合（開いている場合）
		if (frame_->isOpen()) {
			key_item_->setActive(true);
		}
		// 枠が開いていない場合
		else {
			key_item_->setActive(false);
			if (frame_->isClose()) {
				frame_->setActiveWithChild(false);
			}
		}

	}

	void PlanetKeyItemFrame::open() {
		if (!frame_->isActive()) frame_->setActiveWithChild(true);
		frame_->open();
	}

	void PlanetKeyItemFrame::close() {
		frame_->close();
	}

	bool PlanetKeyItemFrame::isOpen() {
		return frame_->isOpen();
	}

	bool PlanetKeyItemFrame::isClose() {
		return frame_->isClose();
	}

	void PlanetKeyItemFrame::setRenderPriority(const float render_priority) {
		frame_->setRenderPriority(render_priority);
		key_item_->render_priority_ = render_priority + 0.0000001f;
	}

	PlanetKeyItemFrame::SharedPtr PlanetKeyItemFrame::create(const std::string file_path) {

		PlanetKeyItemFrame::SharedPtr ptr = dxe::Mover::create<PlanetKeyItemFrame>();

		const int FRAME_WIDTH = 256;
		const int FRAME_HEIGHT = 256;

		// 枠の生成
		UIFrameDesc desc;
		desc.width_ = FRAME_WIDTH;
		desc.height_ = FRAME_HEIGHT;
		desc.interval_ = 19;
		desc.render_position_from_camera_ = 0.0f;
		desc.inner_color_ = t2k::Color(0.5f);
		ptr->frame_ = UIFrame::create(desc);
		ptr->frame_->is_update_always_ = true;
		ptr->pushChild(ptr->frame_);

		// アイテムの生成
		ptr->key_item_ = dxe::Sprite::createFromFile(file_path);
		ptr->key_item_->transform_.scale_ = 6.0f;
		ptr->key_item_->render_position_from_camera_ = 0.0f;
		ptr->key_item_->is_update_always_ = true;
		ptr->key_item_->setActive(false);
		ptr->pushChild(ptr->key_item_);

		ptr->transform_.position_ = t2k::Vector3(0.0f, -100.0f, 0.0f);

		return ptr;
	}

}
