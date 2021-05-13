#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class DemoMovie final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<DemoMovie>;
		using WeakPtr = std::weak_ptr<DemoMovie>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// ����Đ��ԍ�
		inline static int movie_num_ = 0;

		// ����
		dxe::MovieSprite::SharedPtr movie_ = nullptr;

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
		DemoMovie() {}
		~DemoMovie() {}
	};

}
