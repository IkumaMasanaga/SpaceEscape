#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class DemoMovie final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<DemoMovie>;
		using WeakPtr = std::weak_ptr<DemoMovie>;
	private:
		//====================================================================================================
		// メンバ変数

		// 動画再生番号
		inline static int movie_num_ = 0;

		// 動画
		dxe::MovieSprite::SharedPtr movie_ = nullptr;

		//====================================================================================================
		// メンバ関数

		// 初期化
		void initialize() final override;

		// 更新
		void lateUpdate() final override;

		// 終了処理
		void finalize() final override;

		//====================================================================================================
	public:
		DemoMovie() {}
		~DemoMovie() {}
	};

}
