#include "volume_slider.h"


namespace spe {

	void VolumeSlider::update() {
		active_->width_ = (int)(FRAME_WIDTH * *volume_);
		// —LŒø—Ê‚Ì•`‰æˆÊ’u‚ð’²ß
		active_->transform_.position_.x = (float)(-(FRAME_WIDTH>>1) + (active_->width_>>1));
		// ‚Â‚Ü‚Ý‚ÌˆÊ’u‚ð•ÏX
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

		// ”wŒi
		dxe::RectRenderer::SharedPtr back = dxe::RectRenderer::create(FRAME_WIDTH, FRAME_HEIGHT, t2k::Color(0.5f));
		ptr->pushChild(back);
		back->render_position_from_camera_ = 0.0f;
		ptr->rects_[0] = back;

		// —LŒø—Ê
		ptr->active_ = dxe::RectRenderer::create((int)(FRAME_WIDTH * *volume), FRAME_HEIGHT, t2k::Color(1.0f));
		ptr->pushChild(ptr->active_);
		ptr->active_->render_position_from_camera_ = 0.0f;
		ptr->rects_[1] = ptr->active_;

		// ˜g
		dxe::RectRenderer::SharedPtr frame = dxe::RectRenderer::create(FRAME_WIDTH, FRAME_HEIGHT, t2k::Color(0.0f), false);
		ptr->pushChild(frame);
		frame->render_position_from_camera_ = 0.0f;
		ptr->rects_[2] = frame;

		// ‚Â‚Ü‚Ý
		dxe::RectRenderer::SharedPtr knob = dxe::RectRenderer::create(KNOB_SIZE, KNOB_SIZE, t2k::Color(1.0f));
		ptr->pushChild(knob);
		knob->render_position_from_camera_ = 0.0f;
		ptr->rects_[3] = knob;
		ptr->knob_position_ = &knob->transform_.position_;

		dxe::RectRenderer::SharedPtr knob_frame = dxe::RectRenderer::create(KNOB_SIZE, KNOB_SIZE, t2k::Color(0.0f), false);
		ptr->pushChild(knob_frame);
		knob_frame->render_position_from_camera_ = 0.0f;
		ptr->rects_[4] = knob_frame;
		ptr->knob_frame_position_ = &knob_frame->transform_.position_;

		return ptr;
	}

}
