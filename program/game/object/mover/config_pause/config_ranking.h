#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class ConfigRanking final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigRanking>;
		using WeakPtr = std::weak_ptr<ConfigRanking>;
	private:
		//====================================================================================================
		// メンバ変数

		// 文字列の親オブジェクト
		dxe::Mover::SharedPtr text_parent_ = nullptr;

		//====================================================================================================
		// メンバ関数

		// 派生先の生成時
		void onCreatedOfMainFrame() final override;

		// 開いているとき
		void onOpenFrame() final override;

		// 閉じているとき
		void onCloseFrame() final override;

		//====================================================================================================
	public:
		ConfigRanking() {}
		~ConfigRanking() {}

		//====================================================================================================
		// メンバ関数

		// 描画優先度の設定
		void setRenderPriority(const float priority) final override;

		//====================================================================================================
	};

}
