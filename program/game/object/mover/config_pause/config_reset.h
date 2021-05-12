#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class ConfigReset final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigReset>;
		using WeakPtr = std::weak_ptr<ConfigReset>;
	private:
		//====================================================================================================
		// �����o�萔

		// �I������
		inline static const int SELECT_YES = 0;
		inline static const int SELECT_NO = 1;

		//====================================================================================================
		// �����o�ϐ�

		// ���C���̕\���e�L�X�g
		dxe::Text::SharedPtr main_text_ = nullptr;

		// �I������
		std::vector<dxe::Text::SharedPtr> select_texts_;

		// �I������
		int select_ = 1;

		// �V�[�P���X�����p
		t2k::Sequence<ConfigReset*> seq_ = t2k::Sequence<ConfigReset*>(this, &ConfigReset::seqGuide);

		//====================================================================================================
		// �����o�֐�

		// �h����̐�����
		void onCreatedOfMainFrame() final override;

		// �J���Ă���Ƃ�
		void onOpenFrame() final override;

		// ���Ă���Ƃ�
		void onCloseFrame() final override;

		// �ē�
		bool seqGuide();

		// ���s
		bool seqExecution();

		//====================================================================================================
	public:
		ConfigReset() {}
		~ConfigReset() {}

		//====================================================================================================
		// �����o�֐�

		// �`��D��x�̐ݒ�
		void setRenderPriority(const float priority) final override;

		//====================================================================================================
	};

}
