#pragma once
#include "render_object.h"


namespace dxe {

	class RectRenderer final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<RectRenderer>;
		using WeakPtr = std::weak_ptr<RectRenderer>;
	private:
		//====================================================================================================
		// �����o�֐�

		// �`��
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		RectRenderer() {}
		~RectRenderer() {}

		//====================================================================================================
		// �����o�ϐ�

		// ��
		int width_ = 32;

		// ����
		int height_ = 32;

		// �F
		t2k::Color color_;

		// �h��Ԃ��t���O
		bool is_fill_ = true;

		//====================================================================================================
		// static�֐�

		// ����
		static RectRenderer::SharedPtr create(const int width, const int height, const t2k::Color& color, const bool is_fill = true);

		//====================================================================================================
	};

}
