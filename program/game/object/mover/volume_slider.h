#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class VolumeSlider final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<VolumeSlider>;
		using WeakPtr = std::weak_ptr<VolumeSlider>;
	private:
		//====================================================================================================
		// メンバ定数

		// 幅
		inline static const int FRAME_WIDTH = 500;

		//====================================================================================================
		// メンバ変数

		// ボリュームへのポインタ
		float* volume_ = nullptr;

		// つまみの座標へのポインタ
		t2k::Vector3* knob_position_ = nullptr;
		t2k::Vector3* knob_frame_position_ = nullptr;

		// ボリュームの有効量
		dxe::RectRenderer::SharedPtr active_ = nullptr;

		// 描画優先度を変更するため
		std::vector<dxe::RectRenderer::SharedPtr> rects_;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update() final override;

		//====================================================================================================
	public:
		VolumeSlider() {}
		~VolumeSlider() {}

		//====================================================================================================
		// メンバ関数

		// 描画優先度の変更
		void setRenderPriority(const float priority);

		// 有効量の色を変更する
		inline void setActiveColor(const mylib::Color& color) { active_->color_ = color; }

		//====================================================================================================
		// static関数

		// 生成
		static VolumeSlider::SharedPtr create(float* volume);

		//====================================================================================================
	};

}
