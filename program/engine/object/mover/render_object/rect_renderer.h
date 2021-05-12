#pragma once
#include "render_object.h"


namespace dxe {

	class RectRenderer final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<RectRenderer>;
		using WeakPtr = std::weak_ptr<RectRenderer>;
	private:
		//====================================================================================================
		// メンバ関数

		// 描画
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		RectRenderer() {}
		~RectRenderer() {}

		//====================================================================================================
		// メンバ変数

		// 幅
		int width_ = 32;

		// 高さ
		int height_ = 32;

		// 色
		t2k::Color color_;

		// 塗りつぶしフラグ
		bool is_fill_ = true;

		//====================================================================================================
		// static関数

		// 生成
		static RectRenderer::SharedPtr create(const int width, const int height, const t2k::Color& color, const bool is_fill = true);

		//====================================================================================================
	};

}
