#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	// 生成構造体
	struct LimitedChaseCamera2DDesc {
		t2k::Vector3* chase_position_ = nullptr;	// 追いかける座標のポインタ
		float lerp_value_ = 0.1f;					// 線形補完をかける値
		t2k::Vector3 top_left_limit_;				// 範囲の左上座標（ワールド座標系）
		t2k::Vector3 bottom_right_limit_;			// 範囲の右下座標（ワールド座標系）
	};

	class LimitedChaseCamera2D final : public dxe::Camera2D {
	public:
		using SharedPtr = std::shared_ptr<LimitedChaseCamera2D>;
		using WeakPtr = std::weak_ptr<LimitedChaseCamera2D>;
	private:
		//====================================================================================================
		// メンバ変数

		// 追いかける座標のポインタ
		t2k::Vector3* chase_position_ = nullptr;

		// 線形補完をかける値
		float lerp_value_ = 0.1f;

		// 範囲の左上座標（ワールド座標系）
		t2k::Vector3 top_left_limit_;

		// 範囲の右下座標（ワールド座標系）
		t2k::Vector3 bottom_right_limit_;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update() final override;

		//====================================================================================================
	public:
		LimitedChaseCamera2D() {}
		~LimitedChaseCamera2D() {}

		//====================================================================================================
		// static関数

		// 生成
		static LimitedChaseCamera2D::SharedPtr create(const LimitedChaseCamera2DDesc& desc);

		//====================================================================================================
	};

}
