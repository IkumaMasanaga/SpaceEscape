#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class Logo final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Logo>;
		using WeakPtr = std::weak_ptr<Logo>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �V�[���J�ڊ�������
		inline static const float TRANSITION_TIME = 1.0f;

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
		Logo() {}
		~Logo() {}
	};

}
