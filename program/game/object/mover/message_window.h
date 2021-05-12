#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class UIFrame;

	class MessageWindow final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<MessageWindow>;
		using WeakPtr = std::weak_ptr<MessageWindow>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �g
		std::shared_ptr<UIFrame> frame_ = nullptr;

		// ����
		dxe::Text::SharedPtr text_ = nullptr;

		// �L�[�̃A�j���[�V����
		dxe::AnimationSprite::SharedPtr c_key_ = nullptr;

		// �L�[�`��t���O
		bool is_active_c_key_ = true;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update() final override;

		//====================================================================================================
	public:
		MessageWindow() {}
		~MessageWindow() {}

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

		// �L�[���L����
		inline bool isActiveCKey() const { return is_active_c_key_; }

		// �L�[�L���t���O�̐ݒ�
		inline void setActiveCKey(const bool is_active) { is_active_c_key_ = is_active; }

		// ������̕ύX
		inline void changeText(const std::string& text) { text_->changeText(text); }

		// �O���t�@�C�����當����̕ύX
		inline void changeTextFromFile(const std::string& file_path) { text_->changeTextFromFile(file_path); }

		//====================================================================================================
		// static�֐�

		// ����
		static MessageWindow::SharedPtr create(const std::string& text);

		// �O���t�@�C�����當�����ݒ肵�Đ���
		static MessageWindow::SharedPtr createFromFile(const std::string& file_path);

		//====================================================================================================
	};

}
