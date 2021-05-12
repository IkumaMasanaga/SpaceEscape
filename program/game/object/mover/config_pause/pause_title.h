#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class PauseTitle final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<PauseTitle>;
		using WeakPtr = std::weak_ptr<PauseTitle>;
	private:
		//====================================================================================================
		// �����o�萔

		// �I������
		inline static const int SELECT_YES = 0;
		inline static const int SELECT_NO = 1;

		//====================================================================================================
		// �����o�ϐ�

		// �I������
		std::vector<dxe::Text::SharedPtr> select_texts_;

		// �`��D��x�̐ݒ�����邽�߂̊Ǘ��p���X�g
		std::list<dxe::Text::SharedPtr> texts_;

		// �I������
		int select_ = 1;

		// �^�C�g���փt���O
		bool to_title_ = false;

		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreatedOfMainFrame() final override;

		// �J���Ă���Ƃ�
		void onOpenFrame() final override;

		// ���Ă���Ƃ�
		void onCloseFrame() final override;

		//====================================================================================================
	public:
		PauseTitle() {}
		~PauseTitle() {}

		//====================================================================================================
		// �����o�֐�

		// �`��D��x�̐ݒ�
		void setRenderPriority(const float priority) final override;

		// �^�C�g���փt���O�̎擾
		inline bool toTitle() const { return to_title_; }

		//====================================================================================================
	};

}
