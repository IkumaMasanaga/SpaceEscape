#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class UIFrame;

	class PlanetKeyItemFrame final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<PlanetKeyItemFrame>;
		using WeakPtr = std::weak_ptr<PlanetKeyItemFrame>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �g
		std::shared_ptr<UIFrame> frame_ = nullptr;

		// �L�[�A�C�e���摜
		dxe::Sprite::SharedPtr key_item_ = nullptr;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update() final override;

		//====================================================================================================
	public:
		PlanetKeyItemFrame() {}
		~PlanetKeyItemFrame() {}

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

		//====================================================================================================
		// static�֐�

		// ����
		static PlanetKeyItemFrame::SharedPtr create(const std::string file_path);

		//====================================================================================================
	};

}
