#include "config_pause_main_frame.h"
#include "../ui_frame.h"


namespace spe {

	void ConfigPauseMainFrame::onCreated() {

		UIFrameDesc frame_desc;
		frame_desc.width_ = 680;
		frame_desc.height_ = 400;
		frame_desc.interval_ = 20;
		frame_desc.inner_color_ = mylib::Color(0.5f);

		frame_ = UIFrame::create(frame_desc);
		pushChild(frame_);
		frame_->is_update_always_ = true;

		onCreatedOfMainFrame();
	}

	void ConfigPauseMainFrame::update() {

		// �g���L���ȏꍇ�i�J���Ă���ꍇ�j
		if (frame_->isOpen()) {
			onOpenFrame();
		}
		// �g���J���Ă��Ȃ��ꍇ
		else {
			onCloseFrame();
			if (frame_->isClose()) {
				frame_->setActiveWithChild(false);
			}
		}

	}

	void ConfigPauseMainFrame::open() {
		if (!frame_->isActive()) frame_->setActiveWithChild(true);
		frame_->open();
	}

	void ConfigPauseMainFrame::close() {
		frame_->close();
	}

	bool ConfigPauseMainFrame::isOpen() {
		return frame_->isOpen();
	}

	bool ConfigPauseMainFrame::isClose() {
		return frame_->isClose();
	}

}
