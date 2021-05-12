#pragma once
#include "render_object.h"


namespace dxe {

	class AnimationSprite final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<AnimationSprite>;
		using WeakPtr = std::weak_ptr<AnimationSprite>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// ���ݐݒ肳��Ă���A�j���[�V�����̖��O
		std::string now_name_ = "none_image";

		// ���ݐݒ肳��Ă���A�j���[�V�����̉摜
		std::vector<t2k::Texture::SharedPtr> now_textures_;

		// �A�j���[�V�����̃��[�v�t���O
		bool is_loop_ = false;

		// ���݂̃A�j���[�V�����̃R�}��
		int now_index_ = 0;

		// �A�j���[�V������������
		float complete_time_ = 0.0f;

		// �A�j���[�V�������s�p
		t2k::TimerFluct<int> animation_;

		// �A�j���[�V�����Ǘ��A�z�z��
		std::unordered_map<std::string, std::vector<t2k::Texture::SharedPtr>> register_textures_;

		//====================================================================================================
		// �����o�֐�

		void update() final override;

		// �`��
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		AnimationSprite() {}
		~AnimationSprite() {}

		//====================================================================================================
		// �����o�ϐ�

		// x������ɔ��]������t���O
		bool is_flip_x_ = false;

		// y������ɔ��]������t���O
		bool is_flip_y_ = false;

		//====================================================================================================
		// �����o�֐�

		// �A�j���[�V�����̓o�^
		void registAnimation(const std::string& animation_name, const std::vector<t2k::Texture::SharedPtr>& textures);

		// �A�j���[�V�����̍Đ�
		void play(const std::string& animation_name, const float complete_time, const bool is_loop);

		// ���ݍĐ����̃A�j���[�V�����̖��O�̎擾
		inline std::string getNowAnimationName() const { return now_name_; }

		// �A�j���[�V�����Đ�����
		inline bool isPlaying() const { return is_loop_ || !animation_.isComplete(); }

		//====================================================================================================

	};

}
