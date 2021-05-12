#pragma once
#include "../../../../engine/dxe.h"


namespace spe {

	class UIFrame;

	class ConfigPauseMenuFrame : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<ConfigPauseMenuFrame>;
		using WeakPtr = std::weak_ptr<ConfigPauseMenuFrame>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �g
		std::shared_ptr<UIFrame> frame_ = nullptr;

		// �I���L�[�������ꂽ��
		bool is_key_pressed_select_ = false;

		// �I�𒆂̍���
		int select_ = 0;

		//====================================================================================================
		// �����o�֐�

		// �h����̐�����
		virtual void onCreatedOfMenuFrame() = 0;

		// ������
		void onCreated() final override;

		// �X�V
		void update() final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�ϐ�

		// ���j���[����
		std::vector<dxe::Text::SharedPtr> texts_;

		// ���b�Z�[�W�E�B���h�E�ɕ\������e�L�X�g�̃t�@�C���p�X
		std::vector<std::string> message_file_path_;

		//====================================================================================================
	public:
		ConfigPauseMenuFrame() {}
		virtual ~ConfigPauseMenuFrame() {}

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

		// �I���L�[�������ꂽ��
		inline bool isKeyPressedSelect() const { return is_key_pressed_select_; }

		// �I�𒆂̍��ڂ̃��b�Z�[�W�E�B���h�E�̃e�L�X�g�t�@�C���p�X�̎擾
		inline std::string getMessageTextFilePath() const { return message_file_path_[select_]; }

		// �I�𒆂̍��ڂ��擾
		inline int getSelectIndex() const { return select_; }

		//====================================================================================================
	};

}
