#include <algorithm>
#include "../../../screen.h"
#include "../camera2d.h"
#include "movie_sprite.h"


namespace dxe {

	void MovieSprite::render(std::shared_ptr<Screen> screen) {
		setBlendMode();

		t2k::Transform t = getWorldTransform();							// 自身のワールド座標
		t2k::Transform ct = screen->getCamera2D()->getWorldTransform();	// 2Dカメラのワールド座標
		float crs = screen->getCamera2D()->render_scale_;	// カメラの描画スケール
		int sw = screen->getWidth() >> 1;					// 描画スクリーンの幅の半分
		int sh = screen->getHeight() >> 1;					// 描画スクリーンの高さの半分
		int rx = sw + (int)((t.position_.x - ct.position_.x * render_position_from_camera_) * crs);		// 描画するワールド座標系の中心X座標
		int ry = sh + (int)((t.position_.y - ct.position_.y * render_position_from_camera_) * crs);		// 描画するワールド座標系の中心Y座標
		float scl = t.scale_ * crs;		// 描画するスケール
		if (is_flip_x_) t.rotation_ += t2k::toRadian(180);

		// スクリーン範囲外ならば描画しない
		if (!t2k::isIntersectRect(t2k::Vector3((float)rx, (float)ry, 0), (int)(movie_->getWidth() * scl), (int)(movie_->getHeight() * scl), screen->getPosition() + t2k::Vector3((float)sw, (float)sh, 0), sw << 1, sh << 1)) return;

		DrawRotaGraph(rx, ry, scl, t.rotation_, movie_->getImage(), true, is_flip_x_ ^ is_flip_y_);
	}

	void MovieSprite::setVolume(float volume) {
		volume_ = std::clamp(volume, 0.0f, 1.0f);
		ChangeMovieVolumeToGraph((int)(volume_ * 255), movie_->getImage());
	}

	void MovieSprite::play(bool is_seek_top) {
		if (is_seek_top) SeekMovieToGraph(movie_->getImage(), 0);
		PlayMovieToGraph(movie_->getImage());
	}

	void MovieSprite::stop() {
		PauseMovieToGraph(movie_->getImage());
	}

	bool MovieSprite::isPlaying() {
		return GetMovieStateToGraph(movie_->getImage());
	}

	MovieSprite::SharedPtr MovieSprite::createFromFile(const std::string& file_path) {
		MovieSprite::SharedPtr ptr = RenderObject::create<MovieSprite>();
		ptr->movie_ = mylib::Movie::createFromFile(file_path);
		return ptr;
	}

}
