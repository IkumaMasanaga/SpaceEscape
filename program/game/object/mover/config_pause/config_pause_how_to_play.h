#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class UIFrame;

	class ConfigPauseHowToPlay final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigPauseHowToPlay>;
		using WeakPtr = std::weak_ptr<ConfigPauseHowToPlay>;
	private:
		//====================================================================================================
		// �����o�ϐ�
		
		// �e�L�X�g
		dxe::Text::SharedPtr texts_[2] = { nullptr };
		
		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreatedOfMainFrame() final override;

		// �J���Ă���
		void onOpenFrame() final override;

		// ���Ă���
		void onCloseFrame() final override;

		//====================================================================================================
	public:
		ConfigPauseHowToPlay() {}
		~ConfigPauseHowToPlay() {}

		//====================================================================================================
		// �����o�֐�

		// �`��D��x�̐ݒ�
		void setRenderPriority(const float priority) final override;

		//====================================================================================================
	};

}
