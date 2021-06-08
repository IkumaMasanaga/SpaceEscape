#include <algorithm>
#include "../../../screen.h"
#include "../camera2d.h"
#include "movie_sprite.h"


namespace dxe {

	void MovieSprite::render(std::shared_ptr<Screen> screen) {
		setBlendMode();

		t2k::Transform t = getWorldTransform();							// ���g�̃��[���h���W
		t2k::Transform ct = screen->getCamera2D()->getWorldTransform();	// 2D�J�����̃��[���h���W
		float crs = screen->getCamera2D()->render_scale_;	// �J�����̕`��X�P�[��
		int sw = screen->getWidth() >> 1;					// �`��X�N���[���̕��̔���
		int sh = screen->getHeight() >> 1;					// �`��X�N���[���̍����̔���
		int rx = sw + (int)((t.position_.x - ct.position_.x * render_position_from_camera_) * crs);		// �`�悷�郏�[���h���W�n�̒��SX���W
		int ry = sh + (int)((t.position_.y - ct.position_.y * render_position_from_camera_) * crs);		// �`�悷�郏�[���h���W�n�̒��SY���W
		float scl = t.scale_ * crs;		// �`�悷��X�P�[��
		if (is_flip_x_) t.rotation_ += t2k::toRadian(180);

		// �X�N���[���͈͊O�Ȃ�Ε`�悵�Ȃ�
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
