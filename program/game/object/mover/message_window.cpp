#include "message_window.h"
#include "ui_frame.h"


namespace spe {

	void MessageWindow::update() {

		// 枠が有効な場合（開いている場合）
		if (frame_->isOpen()) {
			text_->setActive(true);
			c_key_->setActive(is_active_c_key_);
		}
		// 枠が開いていない場合
		else {
			text_->setActive(false);
			c_key_->setActive(false);
			if (frame_->isClose()) {
				frame_->setActiveWithChild(false);
			}
		}
	}

	void MessageWindow::open() {
		if (!frame_->isActive()) frame_->setActiveWithChild(true);
		frame_->open();
	}

	void MessageWindow::close() {
		frame_->close();
	}

	bool MessageWindow::isOpen() {
		return frame_->isOpen();
	}

	bool MessageWindow::isClose() {
		return frame_->isClose();
	}

	void MessageWindow::setRenderPriority(const float render_priority) {
		frame_->setRenderPriority(render_priority);
		text_->render_priority_ = render_priority + 0.0000001f;
		c_key_->render_priority_ = render_priority + 0.0000002f;
	}

	MessageWindow::SharedPtr MessageWindow::create(const std::string& text) {
		MessageWindow::SharedPtr ptr = dxe::Mover::create<MessageWindow>();
		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		const int FRAME_WIDTH = WINDOW_WIDTH - 64;
		const int FRAME_HEIGHT = 150;

		// 枠の生成
		UIFrameDesc desc;
		desc.width_ = FRAME_WIDTH;
		desc.height_ = FRAME_HEIGHT;
		desc.interval_ = 20;
		desc.render_position_from_camera_ = 0.0f;
		desc.inner_color_ = t2k::Color(0.5f);
		ptr->frame_ = UIFrame::create(desc);
		ptr->frame_->is_update_always_ = true;
		ptr->pushChild(ptr->frame_);

		// 文字列
		ptr->text_ = dxe::Text::create(text);
		ptr->pushChild(ptr->text_);
		ptr->text_->align_mode_x_ = dxe::AlignModeX::CENTER;
		ptr->text_->align_mode_y_ = dxe::AlignModeY::MIDDLE;
		ptr->text_->font_size_ = 24;
		ptr->text_->interval_ = 10;
		ptr->text_->render_position_from_camera_ = 0.0f;
		ptr->text_->is_update_always_ = true;
		ptr->text_->setActive(false);

		// キー
		const int KEY_INTERVAL = 32;

		ptr->c_key_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		ptr->pushChild(ptr->c_key_);
		ptr->c_key_->transform_.position_ = t2k::Vector3((float)((FRAME_WIDTH>>1) - KEY_INTERVAL), (FRAME_HEIGHT>>1) - KEY_INTERVAL, 0);
		ptr->c_key_->registAnimation("c_key", t2k::Texture::createVectorFromFile("graphics/ui/key_c.png", 2, 2, 1, 32, 32));
		ptr->c_key_->play("c_key", 0.8f, true);
		ptr->c_key_->render_position_from_camera_ = 0.0f;
		ptr->c_key_->is_update_always_ = true;
		ptr->c_key_->setActive(false);

		ptr->transform_.position_ = t2k::Vector3(0, WINDOW_HEIGHT * 0.3f, 0);

		return ptr;
	}
	
	MessageWindow::SharedPtr MessageWindow::createFromFile(const std::string& file_path) {
		MessageWindow::SharedPtr ptr = dxe::Mover::create<MessageWindow>();
		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		const int FRAME_WIDTH = WINDOW_WIDTH - 64;
		const int FRAME_HEIGHT = 150;

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

		// 文字列
		ptr->text_ = dxe::Text::createFromFile(file_path);
		ptr->pushChild(ptr->text_);
		ptr->text_->align_mode_x_ = dxe::AlignModeX::CENTER;
		ptr->text_->align_mode_y_ = dxe::AlignModeY::MIDDLE;
		ptr->text_->font_size_ = 24;
		ptr->text_->interval_ = 10;
		ptr->text_->render_position_from_camera_ = 0.0f;
		ptr->text_->is_update_always_ = true;
		ptr->text_->setActive(false);

		// キー
		const int KEY_INTERVAL = 32;
		
		ptr->c_key_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		ptr->pushChild(ptr->c_key_);
		ptr->c_key_->transform_.position_ = t2k::Vector3((float)((FRAME_WIDTH>>1) - KEY_INTERVAL), (FRAME_HEIGHT>>1) - KEY_INTERVAL, 0);
		ptr->c_key_->registAnimation("c_key", t2k::Texture::createVectorFromFile("graphics/ui/key_c.png", 2, 2, 1, 32, 32));
		ptr->c_key_->play("c_key", 0.8f, true);
		ptr->c_key_->render_position_from_camera_ = 0.0f;
		ptr->c_key_->is_update_always_ = true;
		ptr->c_key_->setActive(false);

		ptr->transform_.position_ = t2k::Vector3(0, WINDOW_HEIGHT * 0.3f, 0);

		return ptr;
	}

}
