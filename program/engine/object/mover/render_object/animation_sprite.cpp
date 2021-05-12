#include "../../../screen.h"
#include "../camera2d.h"
#include "animation_sprite.h"


namespace dxe {

	void AnimationSprite::update() {
		// �A�j���[�V�����̍X�V �I�����Ă��Ȃ��ꍇ�͊֐��𔲂���
		if (!animation_.isCompleteUpdate()) return;
		// ���[�v�t���O�������Ă���ꍇ�͎��̃A�j���[�V�����̐ݒ������
		if (is_loop_) {
			now_index_ = 0;
			animation_.setMethodLinear(&now_index_, now_textures_.size(), complete_time_);
		}
	}

	void AnimationSprite::render(std::shared_ptr<Screen> screen) {
		setBlendMode();

		t2k::Transform t = getWorldTransform();							// ���g�̃��[���h���W
		t2k::Transform ct = screen->getCamera2D()->getWorldTransform();	// 2D�J�����̃��[���h���W
		float crs = screen->getCamera2D()->render_scale_;	// �J�����̕`��X�P�[��
		int sw = screen->getWidth() >> 1;					// �`��X�N���[���̕��̔���
		int sh = screen->getHeight() >> 1;					// �`��X�N���[���̍����̔���
		int rx = sw + (int)((t.position_.x - ct.position_.x * render_position_from_camera_) * crs);		// �`�悷�郏�[���h���W�n�̒��SX���W
		int ry = sh + (int)((t.position_.y - ct.position_.y * render_position_from_camera_) * crs);		// �`�悷�郏�[���h���W�n�̒��SY���W
		float scl = t.scale_ * crs;		// �`�悷��X�P�[��

		// ����X���ɑ΂��Ĕ��]�t���O�������Ă����180�x��]������
		if (is_flip_x_) t.rotation_ += t2k::toRadian(180);	

		// �X�N���[���͈͊O�Ȃ�Ε`�悵�Ȃ�
		if (!t2k::isIntersectRect(t2k::Vector3((float)rx, (float)ry, 0), (int)(now_textures_[now_index_]->getWidth() * scl), (int)(now_textures_[now_index_]->getHeight() * scl), screen->getPosition() + t2k::Vector3((float)sw, (float)sh, 0), sw << 1, sh << 1)) return;

		DrawRotaGraph(rx, ry, scl, t.rotation_, now_textures_[now_index_]->getImage(), true, is_flip_x_ ^ is_flip_y_);

	}

	void AnimationSprite::registAnimation(const std::string& animation_name, const std::vector<t2k::Texture::SharedPtr>& textures) {
		// ���ɓo�^���Ă���ꍇ
		if (register_textures_.find(animation_name) != register_textures_.end()) {
			warningMassage(("�A�j���[�V���������d�����Ă��܂� : " + animation_name).c_str());
			return;
		}
		register_textures_.try_emplace(animation_name, textures);
	}

	void AnimationSprite::play(const std::string& animation_name, const float complete_time, const bool is_loop) {
		std::unordered_map<std::string, std::vector<t2k::Texture::SharedPtr>>::iterator it = register_textures_.find(animation_name);
		// �Đ����悤�Ƃ����A�j���[�V�������o�^����Ă��Ȃ������ꍇ
		if (it == register_textures_.end()) {
			warningMassage(("�A�j���[�V�������o�^����Ă��܂��� : " + animation_name).c_str());
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
