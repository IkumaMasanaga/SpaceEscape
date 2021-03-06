#include "volume_slider.h"


namespace spe {

	void VolumeSlider::update() {
		active_->width_ = (int)(FRAME_WIDTH * *volume_);
		// 有効量の描画位置を調節
		active_->transform_.position_.x = (float)(-(FRAME_WIDTH>>1) + (active_->width_>>1));
		// つまみの位置を変更
		knob_frame_position_->x = knob_position_->x = (float)(-(FRAME_WIDTH>>1) + active_->width_);
	}

	void VolumeSlider::setRenderPriority(const float priority) {
		for (int i = 0; i < (int)rects_.size(); ++i) {
			rects_[i]->render_priority_ = priority + (0.0000001f * i);
		}
	}

	VolumeSlider::SharedPtr VolumeSlider::create(float* volume) {
		
		VolumeSlider::SharedPtr ptr = dxe::Mover::create<VolumeSlider>();

		ptr->volume_ = volume;
		ptr->rects_.resize(5);

		const int FRAME_HEIGHT = 10;
		const int KNOB_SIZE = 20;

		// 背景
		dxe::RectRenderer::SharedPtr back = dxe::RectRenderer::create(FRAME_WIDTH, FRAME_HEIGHT, mylib::Color(0.5f));
		ptr->pushChild(back);
		back->render_position_from_camera_ = 0.0f;
		ptr->rects_[0] = back;

		// 有効量
		ptr->active_ = dxe::RectRenderer::create((int)(FRAME_WIDTH * *volume), FRAME_HEIGHT, mylib::Color(1.0f));
		ptr->pushChild(ptr->active_);
		ptr->active_->render_position_from_camera_ = 0.0f;
		ptr->rects_[1] = ptr->active_;

		// 枠
		dxe::RectRenderer::SharedPtr frame = dxe::RectRenderer::create(FRAME_WIDTH, FRAME_HEIGHT, mylib::Color(0.0f), false);
		ptr->pushChild(frame);
		frame->render_position_from_camera_ = 0.0f;
		ptr->rects_[2] = frame;

		// つまみ
		dxe::RectRenderer::SharedPtr knob = dxe::RectRenderer::create(KNOB_SIZE, KNOB_SIZE, mylib::Color(1.0f));
		ptr->pushChild(knob);
		knob->render_position_from_camera_ = 0.0f;
		ptr->rects_[3] = knob;
		ptr->knob_position_ = &knob->transform_.position_;

		dxe::RectRenderer::SharedPtr knob_frame = dxe::RectRenderer::create(KNOB_SIZE, KNOB_SIZE, mylib::Color(0.0f), false);
		ptr->pushChild(knob_frame);
		knob_frame->render_position_from_camera_ = 0.0f;
		ptr->rects_[4] = knob_frame;
		ptr->knob_frame_position_ = &knob_frame->transform_.position_;

		return ptr;
	}

}
