#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class Logo final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Logo>;
		using WeakPtr = std::weak_ptr<Logo>;
	private:
		//====================================================================================================
		// メンバ変数

		// シーン遷移完了時間
		inline static const float TRANSITION_TIME = 1.0f;

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
		Logo() {}
		~Logo() {}
	};

}
