#include "../../../screen.h"
#include "../camera2d.h"
#include "animation_sprite.h"


namespace dxe {

	void AnimationSprite::update() {
		// アニメーションの更新 終了していない場合は関数を抜ける
		if (!animation_.isCompleteUpdate()) return;
		// ループフラグが立っている場合は次のアニメーションの設定をする
		if (is_loop_) {
			now_index_ = 0;
			animation_.setMethodLinear(&now_index_, now_textures_.size(), complete_time_);
		}
	}

	void AnimationSprite::render(std::shared_ptr<Screen> screen) {
		setBlendMode();

		t2k::Transform t = getWorldTransform();							// 自身のワールド座標
		t2k::Transform ct = screen->getCamera2D()->getWorldTransform();	// 2Dカメラのワールド座標
		float crs = screen->getCamera2D()->render_scale_;	// カメラの描画スケール
		int sw = screen->getWidth() >> 1;					// 描画スクリーンの幅の半分
		int sh = screen->getHeight() >> 1;					// 描画スクリーンの高さの半分
		int rx = sw + (int)((t.position_.x - ct.position_.x * render_position_from_camera_) * crs);		// 描画するワールド座標系の中心X座標
		int ry = sh + (int)((t.position_.y - ct.position_.y * render_position_from_camera_) * crs);		// 描画するワールド座標系の中心Y座標
		float scl = t.scale_ * crs;		// 描画するスケール

		// もしX軸に対して反転フラグが立っていれば180度回転させる
		if (is_flip_x_) t.rotation_ += t2k::toRadian(180);	

		// スクリーン範囲外ならば描画しない
		if (!t2k::isIntersectRect(t2k::Vector3((float)rx, (float)ry, 0), (int)(now_textures_[now_index_]->getWidth() * scl), (int)(now_textures_[now_index_]->getHeight() * scl), screen->getPosition() + t2k::Vector3((float)sw, (float)sh, 0), sw << 1, sh << 1)) return;

		DrawRotaGraph(rx, ry, scl, t.rotation_, now_textures_[now_index_]->getImage(), true, is_flip_x_ ^ is_flip_y_);

	}

	void AnimationSprite::registAnimation(const std::string& animation_name, const std::vector<t2k::Texture::SharedPtr>& textures) {
		// 既に登録してある場合
		if (register_textures_.find(animation_name) != register_textures_.end()) {
			warningMassage(("アニメーション名が重複しています : " + animation_name).c_str());
			return;
		}
		register_textures_.try_emplace(animation_name, textures);
	}

	void AnimationSprite::play(const std::string& animation_name, const float complete_time, const bool is_loop) {
		std::unordered_map<std::string, std::vector<t2k::Texture::SharedPtr>>::iterator it = register_textures_.find(animation_name);
		// 再生しようとしたアニメーションが登録されていなかった場合
		if (it == register_textures_.end()) {
			warningMassage(("アニメーションが登録されていません : " + animation_name).c_str());
			return;
		}
		now_name_ = it->first;
		now_textures_ = it->second;
		now_index_ = 0;
		is_loop_ = is_loop;
		complete_time_ = complete_time;
		if (is_loop_) {
			animation_.setMethodLinear(&now_index_, now_textures_.size(), complete_time_);
		}
		else {
			animation_.setMethodLinear(&now_index_, now_textures_.size() - 1, complete_time_);
		}
	}

}
