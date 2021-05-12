#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class Pause;
	class SpacePlayer;
	class SpaceWarpPoint;

	class Space final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Space>;
		using WeakPtr = std::weak_ptr<Space>;
	private:
		//====================================================================================================
		// メンバ定数

		// 背景のカメラからの描画距離
		inline static const float BACKGROUND_RENDER_POSITION_FROM_CAMERA = 0.25f;

		//====================================================================================================
		// メンバ変数

		t2k::Sequence<Space*> seq_ = t2k::Sequence<Space*>(this, &Space::seqPlay);

		// 前にいた惑星の番号
		int prev_planet_id_ = -1;

		// 逃げ出し判定のライン
		int goal_line_ = 0;

		// 背景
		dxe::Sprite::SharedPtr bg1_ = nullptr;
		dxe::Sprite::SharedPtr bg2_ = nullptr;

		// 視界の赤枠
		dxe::Sprite::SharedPtr view_red_ = nullptr;

		// 視界の赤枠のアルファ値
		float red_alpha_ = 0.5f;

		// 警告SEの再生間隔用カウンタ
		float warning_time_count_ = 0.0f;
		
		// アルファ値の制御用
		t2k::TimerFluct<float> red_alpha_controller_;

		// 背景の幅
		int bg_width_ = 0;

		// プレイヤー
		std::shared_ptr<SpacePlayer> player_ = nullptr;

		// ワープポイント
		std::vector<std::shared_ptr<SpaceWarpPoint>> warp_points_;

		// ポーズ
		std::shared_ptr<Pause> pause_ = nullptr;

		//====================================================================================================
		// メンバ関数

		// 初期化
		void initialize() final override;

		// 更新
		void lateUpdate() final override;

		// 終了処理
		void finalize() final override;

		// プレイシーケンス
		bool seqPlay();

		// ポーズシーケンス
		bool seqPause();

		//====================================================================================================
	public:
		Space() {}
		~Space() {}

		//====================================================================================================
		// static関数

		// 生成
		static Space::SharedPtr create(const int prev_planet_id);

		//====================================================================================================
	};

}
