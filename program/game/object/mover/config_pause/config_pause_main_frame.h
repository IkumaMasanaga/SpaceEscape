#pragma once
#include "../../../../engine/dxe.h"


namespace spe {

	class UIFrame;

	class ConfigPauseMainFrame : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<ConfigPauseMainFrame>;
		using WeakPtr = std::weak_ptr<ConfigPauseMainFrame>;
	private:
		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreated() final override;

		// �X�V
		void update() final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�ϐ�

		// �g
		std::shared_ptr<UIFrame> frame_ = nullptr;

		//====================================================================================================
		// �����o�֐�

		// �h����̐�����
		virtual void onCreatedOfMainFrame() = 0;

		// �J���Ă���Ƃ��̏���
		virtual void onOpenFrame() = 0;

		// ���Ă���Ƃ��i�󂢂Ă��Ȃ����j�̏���
		// ����A�J���r�������s�����
		virtual void onCloseFrame() = 0;

		//====================================================================================================
	public:
		ConfigPauseMainFrame() {}
		virtual ~ConfigPauseMainFrame() {}

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

		// �`��D��x�̐ݒ�
		virtual void setRenderPriority(const float priority) = 0;

		//====================================================================================================
	};

}
