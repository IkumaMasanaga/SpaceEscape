#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	// 生成構造体
	struct UIFrameDesc final {
		bool is_open_ = false;		// 生成時に既に開いているかフラグ
		int width_ = 200;			// 幅
		int height_ = 400;			// 高さ
		int interval_ = 10;			// 外と中の枠の間隔
		float action_time_ = 0.1f;	// 横、縦に開ききる、閉じきるまでの時間
		float back_alpha_ = 0.5f;	// 背景のアルファ値
		float render_position_from_camera_ = 0.0f;	// カメラの影響割合
		t2k::Color back_color_ = t2k::Color(0.5f);	// 背景の色
		t2k::Color frame_color_ = t2k::Color(1.0f);	// 外枠の色
		t2k::Color inner_color_ = t2k::Color(1.0f);	// 内枠の色
	};

	class UIFrame : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<UIFrame>;
		using WeakPtr = std::weak_ptr<UIFrame>;
	private:
		//====================================================================================================
		// メンバ定数

		// 最小サイズ
		static const int MIN_SIZE = 2;

		//====================================================================================================
		// メンバ変数

		// 開くか
		bool is_open_ = true;

		// 閉じるか
		bool is_close_ = false;

		// 幅のポインタ
		int* width_ = nullptr;
		int* frame_width_ = nullptr;
		int* inner_width_ = nullptr;

		// 最大の幅
		int max_width_ = 32;

		// 高さのポインタ
		int* height_ = nullptr;
		int* frame_height_ = nullptr;
		int* inner_height_ = nullptr;

		// 最大の高さ
		int max_height_ = 32;

		// 枠の間隔
		int interval_ = 10;

		// アニメーション時間
		float action_time_ = 0.1f;

		// 描画優先度のポインタ
		float* back_priority_ = nullptr;
		float* frame_priority_ = nullptr;
		float* inner_priority_ = nullptr;

		// 幅、高さのアニメーション処理用
		t2k::TimerFluct<int> size_controller_;

		// シーケンス処理用
		t2k::Sequence<UIFrame*> seq_ = t2k::Sequence<UIFrame*>(this, &UIFrame::seqOpen);

		//====================================================================================================
		// メンバ関数

		// 更新
		void update() final override;

		// 開いているとき
		bool seqOpen();

		// 待機
		bool seqIdle();

		// 閉じているとき
		bool seqClose();

		//====================================================================================================
	public:
		UIFrame() {}
		~UIFrame() {}

		//====================================================================================================
		// メンバ関数

		// 開く
		void open();

		// 閉じる
		void close();
		
		// 開いているか
		bool isOpen();

		// 閉じているか
		bool isClose();

		// 描画優先度の変更
		void setRenderPriority(const float render_priority);

		//====================================================================================================
		// static関数

		static UIFrame::SharedPtr create(const UIFrameDesc& desc);

		//====================================================================================================
	};

}
