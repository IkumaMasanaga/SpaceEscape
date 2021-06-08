#include "dx_engine.h"
#include "collision_manager.h"
#include "physics.h"
#include "bgm_manager.h"
#include "se_manager.h"
#include "joypad_manager.h"
#include "scene.h"
#include "object/object.h"


namespace dxe {

	void DxEngine::initialize(const int window_width, const int window_height, std::shared_ptr<Scene> start) {
		window_width_ = window_width;
		window_height_ = window_height;
		now_scene_ = next_scene_ = start;
		now_scene_->initialize();
	}

	void DxEngine::update() {
		JoypadManager::getInstance().update();
		now_scene_->update();
		transition_sequence_.update();
		now_scene_->render();
		if (!isInTransition()) return;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(transition_alpha_ * 255));
		DrawFillBox(0, 0, window_width_, window_height_, transition_color_.toInt());
	}

	bool DxEngine::seqFadeIn() {
		if (transition_sequence_.isStart()) {
			transition_controller_.setMethodLinear(&transition_alpha_, 0.0f, transition_complete_time_);
		}
		// シーン遷移のアルファ値が0.0fになったら
		if (transition_controller_.isCompleteUpdate()) {
			transition_sequence_.change(&DxEngine::seqIdle);
		}
		return true;
	}

	bool DxEngine::seqIdle() {
		return true;
	}

	bool DxEngine::seqFadeOut() {
		if (transition_sequence_.isStart()) {
			transition_controller_.setMethodLinear(&transition_alpha_, 1.0f, transition_complete_time_);
		}
		// シーン遷移のアルファ値が1.0fになったら
		if (transition_controller_.isCompleteUpdate()) {
			// 次のシーンが設定されていなければゲーム終了
			if (now_scene_ == next_scene_) {
				is_playing_game_ = false;
				return false;
			}
			transition_sequence_.change(&DxEngine::seqFadeIn);
			now_scene_->finalize();
			now_scene_ = next_scene_;
			Object::instance_count_ = 0;
			BGMManager::getInstance().releaceAll();
			SEManager::getInstance().releaceAll();
			CollisionManager::destroy();
			Physics::destroy();
			now_scene_->initialize();
			t2k::Texture::releaseUnique();
			mylib::Audio::releaseUnique();
			mylib::Movie::releaseUnique();
		}
		return true;
	}

	void DxEngine::finalize() {
		BGMManager::destroy();
		SEManager::destroy();
		CollisionManager::destroy();
		Physics::destroy();
	}

}
