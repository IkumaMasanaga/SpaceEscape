#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class VolumeSlider;

	class ConfigPauseVolume final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigPauseVolume>;
		using WeakPtr = std::weak_ptr<ConfigPauseVolume>;
	private:
		//====================================================================================================
		// �����o�萔

		// �I������
		inline static const int SELECT_BGM = 0;
		inline static const int SELECT_SE = 1;

		//====================================================================================================
		// �����o�ϐ�

		// �V�[�P���X
		t2k::Sequence<ConfigPauseVolume*> seq_ = t2k::Sequence<ConfigPauseVolume*>(this, &ConfigPauseVolume::seqMenu);

		// BGM�p�X���C�_�[
		std::shared_ptr<VolumeSlider> bgm_slider_ = nullptr;

		// SE�p�X���C�_�[
		std::shared_ptr<VolumeSlider> se_slider_ = nullptr;

		// �e�L�X�g
		std::vector<dxe::Text::SharedPtr> texts_;

		// �I������
		int select_ = 0;

		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreatedOfMainFrame() final override;

		// �J���Ă���Ƃ�
		void onOpenFrame() final override;

		// ���Ă���Ƃ�
		void onCloseFrame() final override;

		// �I��
		bool seqMenu();

		// BGM����
		bool seqBGM();

		// SE����
		bool seqSE();

		//====================================================================================================
	public:
		ConfigPauseVolume() {}
		~ConfigPauseVolume() {}

		//====================================================================================================

		// �`��D��x�̐ݒ�
		void setRenderPriority(const float priority) final override;

		//====================================================================================================
	};

}
