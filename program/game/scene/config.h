#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class MessageWindow;
	class ConfigMenu;
	class ConfigPauseHowToPlay;
	class ConfigItem;
	class ConfigEnding;
	class ConfigRanking;
	class ConfigPauseVolume;
	class ConfigReset;

	class Config final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Config>;
		using WeakPtr = std::weak_ptr<Config>;
	private:
		//====================================================================================================
		// �����o�萔

		// ���j���[�̍��W
		inline static const t2k::Vector3 MENU_FRAME_POSITION = t2k::Vector3(-354.0f, -80.0f, 0.0f);

		// ���C���t���[���̍��W
		inline static const t2k::Vector3 MAIN_FRAME_POSITION = t2k::Vector3(140.0f, -80.0f, 0.0f);

		//====================================================================================================
		// �����o�ϐ�

		t2k::Sequence<Config*> seq_ = t2k::Sequence<Config*>(this, &Config::seqMenu);

		// ���b�Z�[�W�E�B���h�E
		std::shared_ptr<MessageWindow> message_window_ = nullptr;

		// ���j���[
		std::shared_ptr<ConfigMenu> menu_frame_ = nullptr;

		// ������@
		std::shared_ptr<ConfigPauseHowToPlay> how_to_play_ = nullptr;

		// �A�C�e��
		std::shared_ptr<ConfigItem> item_ = nullptr;

		// �G���f�B���O
		std::shared_ptr<ConfigEnding> ending_ = nullptr;

		// �����L���O
		std::shared_ptr<ConfigRanking> ranking_ = nullptr;

		// �{�����[��
		std::shared_ptr<ConfigPauseVolume> volume_ = nullptr;

		// ���Z�b�g
		std::shared_ptr<ConfigReset> reset_ = nullptr;

		//====================================================================================================
		// �����o�֐�

		// ������
		void initialize() final override;

		// �X�V
		void lateUpdate() final override;

		// �I������
		void finalize() final override;

		// ���j���[
		bool seqMenu();

		// �������
		bool seqHowToPlay();

		// �A�C�e��
		bool seqItem();

		// �G���f�B���O
		bool seqEnding();

		// �����L���O
		bool seqRanking();

		// �{�����[��
		bool seqVolume();

		// ���Z�b�g
		bool seqReset();

		//====================================================================================================
	public:
		Config() {}
		~Config() {}
	};

}
