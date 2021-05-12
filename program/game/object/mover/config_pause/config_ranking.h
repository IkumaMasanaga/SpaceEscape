#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class ConfigRanking final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigRanking>;
		using WeakPtr = std::weak_ptr<ConfigRanking>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// ������̐e�I�u�W�F�N�g
		dxe::Mover::SharedPtr text_parent_ = nullptr;

		//====================================================================================================
		// �����o�֐�

		// �h����̐�����
		void onCreatedOfMainFrame() final override;

		// �J���Ă���Ƃ�
		void onOpenFrame() final override;

		// ���Ă���Ƃ�
		void onCloseFrame() final override;

		//====================================================================================================
	public:
		ConfigRanking() {}
		~ConfigRanking() {}

		//====================================================================================================
		// �����o�֐�

		// �`��D��x�̐ݒ�
		void setRenderPriority(const float priority) final override;

		//====================================================================================================
	};

}
