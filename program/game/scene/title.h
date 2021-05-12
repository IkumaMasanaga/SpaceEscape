#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class Title final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Title>;
		using WeakPtr = std::weak_ptr<Title>;
	private:
		//====================================================================================================
		// �����o�萔

		// �I�����ڂ̔ԍ�
		inline static const int SELECT_START = 0;
		inline static const int SELECT_CONFIG = 1;
		inline static const int SELECT_EXIT = 2;

		//====================================================================================================
		// �����o�ϐ�

		// PRESS [ C ] TO START
		dxe::Text::SharedPtr press_c_ = nullptr;

		// �I�����ڂ̐e�I�u�W�F�N�g
		dxe::Mover::SharedPtr select_parent_ = nullptr;

		// �I�����ڂ̐F��ύX���邽�߂̔z��
		std::vector<dxe::Text::SharedPtr> select_texts_;

		// ���ݑI�𒆂̗v�f
		unsigned int selected_ = 0;

		// �V�[�P���X�����p
		t2k::Sequence<Title*> seq_ = t2k::Sequence<Title*>(this, &Title::seqPressC);

		//====================================================================================================
		// �����o�֐�

		// ������
		void initialize() final override;

		// �X�V
		void lateUpdate() final override;

		// �I������
		void finalize() final override;
		
		// �ŏ��̃V�[�P���X
		bool seqPressC();

		// ���j���[�I���V�[�P���X
		bool seqSelectMenu();

		//====================================================================================================
	public:
		Title() {}
		~Title() {}
	};

}
