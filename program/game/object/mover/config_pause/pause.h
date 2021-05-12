#pragma once
#include "../../../../engine/dxe.h"


namespace spe {

	class MessageWindow;
	class PauseMenu;
	class ConfigPauseHowToPlay;
	class PauseItem;
	class ConfigPauseVolume;
	class PauseTitle;

	class Pause final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<Pause>;
		using WeakPtr = std::weak_ptr<Pause>;
	private:
		//====================================================================================================
		// �����o�萔

		// �`��D��x
		inline static const float PRIORITY = 100.0f;

		// ���j���[�̍��W
		inline static const t2k::Vector3 MENU_FRAME_POSITION = t2k::Vector3(-354.0f, -80.0f, 0.0f);

		// ���C���t���[���̍��W
		inline static const t2k::Vector3 MAIN_FRAME_POSITION = t2k::Vector3(140.0f, -80.0f, 0.0f);

		//====================================================================================================
		// �����o�ϐ�

		// �V�[�P���X�����p
		t2k::Sequence<Pause*> seq_ = t2k::Sequence<Pause*>(this, &Pause::seqMenu);

		// ���b�Z�[�W�E�B���h�E
		std::shared_ptr<MessageWindow> message_window_ = nullptr;

		// ���j���[
		std::shared_ptr<PauseMenu> menu_frame_ = nullptr;

		// ������@
		std::shared_ptr<ConfigPauseHowToPlay> how_to_play_ = nullptr;

		// �A�C�e��
		std::shared_ptr<PauseItem> item_ = nullptr;

		// �{�����[��
		std::shared_ptr<ConfigPauseVolume> volume_ = nullptr;

		// �^�C�g����
		std::shared_ptr<PauseTitle> title_ = nullptr;

		// �|�[�Y�I���t���O
		bool is_end_ = false;

		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreated() final override;

		// �X�V
		void update() final override;

		// ���C��
		bool seqMenu();

		// �������
		bool seqHowToPlay();

		// �l���σA�C�e��
		bool seqItems();

		// �{�����[�����C��
		bool seqVolume();

		// �^�C�g��
		bool seqTitle();

		// �󂢂Ă���t���[�������ׂĕ���
		void closeFrames();

		//====================================================================================================
	public:
		Pause() {}
		~Pause() {}

		//====================================================================================================
		// �����o�֐�

		// �^�C�g���֐i�ނ�
		bool toTitle() const;

		// �|�[�Y�I����
		inline bool isEnd() const { return is_end_; }

		//====================================================================================================
	};

}
