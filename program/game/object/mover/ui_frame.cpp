#include "ui_frame.h"


namespace spe {

	void UIFrame::update() {
		seq_.update();
	}

	bool UIFrame::seqOpen() {

		// 開く処理を開始したとき
		if (seq_.isStart()) {
			// まず幅から
			size_controller_.setMethodLinear(width_, max_width_, action_time_);
		}
		// アニメーションが終了するまで
		if (size_controller_.isCompleteUpdate()) {
			// 高さが最大の高さである場合は終了
			if (*height_ == max_height_) {
				seq_.change(&UIFrame::seqIdle);
				is_open_ = false;
			}
			else {
				// 高さも変動させる
				size_controller_.setMethodLinear(height_, max_height_, action_time_);
			}
		}

		// 幅、高さを変動させる
		*frame_width_ = *width_;
		*inner_width_ = (*width_ - interval_ < 0) ? 0 : *width_ - interval_;
		*frame_height_ = *height_;
		*inner_height_ = (*height_ - interval_ < 0) ? 0 : *height_ - interval_;

		return true;
	}

	bool UIFrame::seqIdle() {
		return true;
	}

	bool UIFrame::seqClose() {

		// 閉じる処理を開始したとき
		if (seq_.isStart()) {
			// まず高さから
			size_controller_.setMethodLinear(height_, MIN_SIZE, action_time_);
		}
		// アニメーションが終了するまで
		if (size_controller_.isCompleteUpdate()) {
			// 幅が最小値である場合は終了
			if (*width_ == MIN_SIZE) {
				seq_.change(&UIFrame::seqIdle);
				is_close_ = false;
			}
			else {
				// 幅も変動させる
				size_controller_.setMethodLinear(width_, MIN_SIZE, action_time_);
			}
		}

		// 幅、高さを変動させる
		*frame_width_ = *width_;
		*inner_width_ = (*width_ - interval_ < 0) ? 0 : *width_ - interval_;
		*frame_height_ = *height_;
		*inner_height_ = (*height_ - interval_ < 0) ? 0 : *height_ - interval_;

		return true;
	}

	void UIFrame::open() {
		if (is_open_ || is_close_ || *width_ != 2) return;
		is_open_ = true;
		seq_.change(&UIFrame::seqOpen);
	}

	void UIFrame::close() {
		if (is_open_ || is_close_ || *height_ != max_height_) return;
		is_close_ = true;
		seq_.change(&UIFrame::seqClose);
	}

	bool UIFrame::isOpen() {
		return !is_open_ && !is_close_ && *height_ == max_height_;
	}

	bool UIFrame::isClose() {
		return !is_open_ && !is_close_ && *width_ == 2;
	}

	void UIFrame::setRenderPriority(const float render_priority) {
		*back_priority_ = render_priority;
		*frame_priority_ = render_priority + 0.00000001f;
		*inner_priority_ = render_priority + 0.00000002f;
	}

	UIFrame::SharedPtr UIFrame::create(const UIFrameDesc& desc) {
		UIFrame::SharedPtr ptr = dxe::Mover::create<UIFrame>();

		// 背景の生成
		dxe::RectRenderer::SharedPtr back = dxe::RectRenderer::create(MIN_SIZE, MIN_SIZE, mylib::Color(0.5f));
		back->alpha_ = desc.back_alpha_;
		back->color_ = desc.back_color_;
		back->render_position_from_camera_ = desc.render_position_from_camera_;
		ptr->width_ = &back->width_;
		ptr->height_ = &back->height_;
		ptr->back_priority_ = &back->render_priority_;
		ptr->pushChild(back);

		// 外枠の生成
		dxe::RectRenderer::SharedPtr frame = dxe::RectRenderer::create(MIN_SIZE, MIN_SIZE, mylib::Color(1.0f), false);
		frame->color_ = desc.frame_color_;
		frame->render_position_from_camera_ = desc.render_position_from_camera_;
		ptr->frame_width_ = &frame->width_;
		ptr->frame_height_ = &frame->height_;
		ptr->frame_priority_ = &frame->render_priority_;
		ptr->pushChild(frame);

		// 内枠の生成
		dxe::RectRenderer::SharedPtr inner_frame = dxe::RectRenderer::create(0, 0, mylib::Color(1.0f), false);
		inner_frame->color_ = desc.inner_color_;
		inner_frame->render_position_from_camera_ = desc.render_position_from_camera_;
		ptr->inner_width_ = &inner_frame->width_;
		ptr->inner_height_ = &inner_frame->height_;
		ptr->inner_priority_ = &inner_frame->render_priority_;
		ptr->pushChild(inner_frame);

		ptr->max_width_ = desc.width_;
		ptr->max_height_ = desc.height_;
		ptr->interval_ = desc.interval_;
		ptr->action_time_ = desc.action_time_;
		
		// 生成時に開くフラグが立っている場合は開かせる
		if (desc.is_open_) {
			*ptr->width_ = ptr->max_width_;
			*ptr->frame_width_ = ptr->max_width_;
			*ptr->inner_width_ = ptr->max_width_ - ptr->interval_;
			*ptr->height_ = ptr->max_height_;
			*ptr->frame_height_ = ptr->max_height_;
			*ptr->inner_height_ = ptr->max_height_ - ptr->interval_;
			ptr->is_open_ = false;
		}

		return ptr;
	}

}
