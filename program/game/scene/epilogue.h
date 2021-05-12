#pragma once
#include "../../engine/dxe.h"


namespace spe {

	enum class EndType;
	class MessageWindow;

	class Epilogue final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Epilogue>;
		using WeakPtr = std::weak_ptr<Epilogue>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		EndType end_type_ = (EndType)0;

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
		Epilogue() {}
		~Epilogue() {}

		//====================================================================================================
		// static�֐�

		// ����
		static Epilogue::SharedPtr create(const EndType& end_type);

		//====================================================================================================
	};

}
