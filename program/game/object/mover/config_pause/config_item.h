#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class ConfigItem final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigItem>;
		using WeakPtr = std::weak_ptr<ConfigItem>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �A�C�e��
		std::vector<dxe::Text::SharedPtr> items_;

		// ���b�Z�[�W�E�B���h�E�ɕ\������e�L�X�g�̃t�@�C���p�X
		std::vector<std::string> message_file_path_;

		// �I���L�[�������ꂽ��
		bool is_key_pressed_select_ = false;

		// �I�𒆂̍���
		int select_ = 0;

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
		ConfigItem() {}
		~ConfigItem() {}

		//====================================================================================================
		// �����o�֐�

		// �`��D��x�̐ݒ�
		void setRenderPriority(const float priority) final override;

		// �I���L�[�������ꂽ��
		inline bool isKeyPressedSelect() const { return is_key_pressed_select_; }

		// �I�𒆂̍��ڂ̃��b�Z�[�W�E�B���h�E�̃e�L�X�g�t�@�C���p�X�̎擾
		inline std::string getMessageTextFilePath() const { return message_file_path_[select_]; }

		//====================================================================================================
	};

}
