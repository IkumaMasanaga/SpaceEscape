#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	// �����\����
	struct BackgroundStarsDesc final {
		int width_ = 0;				// ������
		int height_ = 0;			// ��������
		int generate_num_ = 100;	// ������
		float render_position_from_camera_ = 0.5f;	// �J��������̋���
		float animation_time_min_ = 0.5f;			// �ŏ��A�j���[�V������������
		float animation_time_max_ = 1.5f;			// �ő�A�j���[�V������������
		float scale_min_ = 0.5f;	// �ŏ��g�嗦
		float scale_max_ = 2.0f;	// �ő�g�嗦
		float priority_ = -1.0f;	// �`��D��x
	};

	// �w�i�̐�
	// AnimationSprite��1��1����������y�����A�eSprite�ŃA�j���[�V�����Ԋu�͓����A�A���t�@�l������
	class BackgroundStars final : public dxe::RenderObject {
	public:
		using SharedPtr = std::shared_ptr<BackgroundStars>;
		using WeakPtr = std::weak_ptr<BackgroundStars>;
	private:
		//====================================================================================================
		// �C���i�[�N���X

		struct BackgroundStar final {
			t2k::Transform transform_;
			int sprite_id_ = 0;
		};

		struct StarSprite final {
			std::vector<t2k::Texture::SharedPtr> textures_;
			int animation_index_ = 0;
			t2k::TimerFluct<int> animation_;
			float complete_time_ = 0.0f;
		};

		//====================================================================================================
		// �����o�ϐ�

		// �`��ʒu��id
		std::vector<BackgroundStar> stars_;

		// �摜�̎�ނƃA�j���[�V����
		std::vector<StarSprite> star_sprites_;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update() final override;

		// �`��
		void render(std::shared_ptr<dxe::Screen> screen) final override;

		//====================================================================================================
	public:
		BackgroundStars() {}
		~BackgroundStars() {}

		//====================================================================================================
		// static�֐�

		// ����
		static BackgroundStars::SharedPtr create(const BackgroundStarsDesc& desc);

		//====================================================================================================
	};

}
