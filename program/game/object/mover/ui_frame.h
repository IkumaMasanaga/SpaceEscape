#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	// �����\����
	struct UIFrameDesc final {
		bool is_open_ = false;		// �������Ɋ��ɊJ���Ă��邩�t���O
		int width_ = 200;			// ��
		int height_ = 400;			// ����
		int interval_ = 10;			// �O�ƒ��̘g�̊Ԋu
		float action_time_ = 0.1f;	// ���A�c�ɊJ������A������܂ł̎���
		float back_alpha_ = 0.5f;	// �w�i�̃A���t�@�l
		float render_position_from_camera_ = 0.0f;	// �J�����̉e������
		t2k::Color back_color_ = t2k::Color(0.5f);	// �w�i�̐F
		t2k::Color frame_color_ = t2k::Color(1.0f);	// �O�g�̐F
		t2k::Color inner_color_ = t2k::Color(1.0f);	// ���g�̐F
	};

	class UIFrame : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<UIFrame>;
		using WeakPtr = std::weak_ptr<UIFrame>;
	private:
		//====================================================================================================
		// �����o�萔

		// �ŏ��T�C�Y
		static const int MIN_SIZE = 2;

		//====================================================================================================
		// �����o�ϐ�

		// �J����
		bool is_open_ = true;

		// ���邩
		bool is_close_ = false;

		// ���̃|�C���^
		int* width_ = nullptr;
		int* frame_width_ = nullptr;
		int* inner_width_ = nullptr;

		// �ő�̕�
		int max_width_ = 32;

		// �����̃|�C���^
		int* height_ = nullptr;
		int* frame_height_ = nullptr;
		int* inner_height_ = nullptr;

		// �ő�̍���
		int max_height_ = 32;

		// �g�̊Ԋu
		int interval_ = 10;

		// �A�j���[�V��������
		float action_time_ = 0.1f;

		// �`��D��x�̃|�C���^
		float* back_priority_ = nullptr;
		float* frame_priority_ = nullptr;
		float* inner_priority_ = nullptr;

		// ���A�����̃A�j���[�V���������p
		t2k::TimerFluct<int> size_controller_;

		// �V�[�P���X�����p
		t2k::Sequence<UIFrame*> seq_ = t2k::Sequence<UIFrame*>(this, &UIFrame::seqOpen);

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update() final override;

		// �J���Ă���Ƃ�
		bool seqOpen();

		// �ҋ@
		bool seqIdle();

		// ���Ă���Ƃ�
		bool seqClose();

		//====================================================================================================
	public:
		UIFrame() {}
		~UIFrame() {}

		//====================================================================================================
		// �����o�֐�

		// �J��
		void open();

		// ����
		void close();
		
		// �J���Ă��邩
		bool isOpen();

		// ���Ă��邩
		bool isClose();

		// �`��D��x�̕ύX
		void setRenderPriority(const float render_priority);

		//====================================================================================================
		// static�֐�

		static UIFrame::SharedPtr create(const UIFrameDesc& desc);

		//====================================================================================================
	};

}
