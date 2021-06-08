#include "one_shot_animation.h"


namespace spe {

	void OneShotAnimation::update() {
		// 各種値を変動させる
		transform_.position_ += (move_ * mylib::Time::getDeltaTime());
		transform_.rotation_ += (angle_per_second_ * mylib::Time::getDeltaTime());
		scale_controller_.isCompleteUpdate();
		alpha_controller_.isCompleteUpdate();
		// アニメーションが終了したら消す
		if (!animation_->isPlaying()) {
			destroyWithChild();
		}
	}

	OneShotAnimation::SharedPtr OneShotAnimation::create(const OneShotAnimationDesc& desc) {

		OneShotAnimation::SharedPtr ptr = dxe::Mover::create<OneShotAnimation>();

		// アニメーション
		ptr->animation_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		ptr->pushChild(ptr->animation_);
		ptr->animation_->alpha_ = desc.start_alpha_;
		ptr->animation_->render_priority_ = desc.render_priority_;
		ptr->animation_->is_flip_x_ = desc.is_flip_x_;
		ptr->animation_->is_flip_y_ = desc.is_flip_y_;
		ptr->animation_->registAnimation("anim", t2k::Texture::createVectorFromFile(desc.file_path_, desc.all_num_, desc.x_num_, desc.y_num_, desc.width_, desc.height_));
		ptr->animation_->play("anim", desc.alive_time_, false);

		ptr->transform_ = { desc.start_position_, desc.start_rotation_, desc.start_scale_ };

		// 各種変動させる値の設定
		ptr->move_ = desc.move_direction_;
		ptr->move_.normalize();
		ptr->move_ *= desc.speed_per_second_;
		ptr->angle_per_second_ = t2k::toRadian(desc.angle_per_second_);
		ptr->scale_controller_.setMethodLinear(&ptr->transform_.scale_, desc.complete_scale_, desc.alive_time_);
		ptr->alpha_controller_.setMethodLinear(&ptr->animation_->alpha_, desc.complete_alpha_, desc.alive_time_);

		return ptr;

	}

}
