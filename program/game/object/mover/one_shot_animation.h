#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	// �����\����
	struct OneShotAnimationDesc {
		std::string file_path_ = "";	// �摜�̃t�@�C���p�X
		int all_num_ = 0;				// ���������ۂ̑���
		int x_num_ = 0;					// �������̕�����
		int y_num_ = 0;					// �c�����̕�����
		int width_ = 0;					// 1��������̕�
		int height_ = 0;				// 1��������̍���

		float alive_time_ = 1.0f;		// ��������

		t2k::Vector3 start_position_ = t2k::Vector3::ZERO;	// �������W
		float start_rotation_ = 0.0f;						// ������]
		float start_scale_ = 1.0f;							// �����X�P�[��
		float start_alpha_ = 1.0f;							// �����A���t�@�l
		t2k::Vector3 move_direction_ = t2k::Vector3::ZERO;	// �ړ��x�N�g��
		float speed_per_second_ = 0.0f;						// ���ԓ�����̈ړ����x
		float angle_per_second_ = 0.0f;						// ���ԓ�����̉�]�p�x
		float complete_scale_ = 1.0f;						// ������Ƃ��̃X�P�[��
		float complete_alpha_ = 1.0f;						// ������Ƃ��̃A���t�@�l
		float render_priority_ = 0.0f;						// �`��D��x
		bool is_flip_x_ = false;							// x������ɔ��]�����邩
		bool is_flip_y_ = false;							// y������ɔ��]�����邩
	};

	class OneShotAnimation final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<OneShotAnimation>;
		using WeakPtr = std::weak_ptr<OneShotAnimation>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �A�j���[�V����
		dxe::AnimationSprite::SharedPtr animation_ = nullptr;

		// ���ԓ�����̉�]�p�i���W�A���j
		float angle_per_second_ = 0.0f;

		// �ړ��x�N�g��
		t2k::Vector3 move_ = t2k::Vector3::ZERO;

		// �X�P�[���̐���p
		t2k::TimerFluct<float> scale_controller_;

		// �A���t�@�l�̐���p
		t2k::TimerFluct<float> alpha_controller_;

		//====================================================================================================
		// �����o�֐�

		void update() final override;

		//====================================================================================================
	public:
		OneShotAnimation() {}
		~OneShotAnimation() {}

		//====================================================================================================
		// static�֐�

		// ����
		static OneShotAnimation::SharedPtr create(const OneShotAnimationDesc& desc);

		//====================================================================================================
	};

}
