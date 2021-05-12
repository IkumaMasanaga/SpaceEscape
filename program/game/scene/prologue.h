#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class MessageWindow;

	class Prologue final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Prologue>;
		using WeakPtr = std::weak_ptr<Prologue>;
	private:
		//====================================================================================================
		// �����o�֐�
		
		// ���b�Z�[�W�E�B���h�E
		std::shared_ptr<MessageWindow> message_window_ = nullptr;
		
		//====================================================================================================
		// �����o�֐�

		// ������
		void initialize() final override;

		// �X�V
		void lateUpdate() final override;

		// �I������
		void finalize() final override;

		//====================================================================================================
	public:
		Prologue() {}
		~Prologue() {}
	};

}
