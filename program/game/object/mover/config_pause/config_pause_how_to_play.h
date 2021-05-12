#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class UIFrame;

	class ConfigPauseHowToPlay final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigPauseHowToPlay>;
		using WeakPtr = std::weak_ptr<ConfigPauseHowToPlay>;
	private:
		//====================================================================================================
		// メンバ変数
		
		// テキスト
		dxe::Text::SharedPtr texts_[2] = { nullptr };
		
		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreatedOfMainFrame() final override;

		// 開いている
		void onOpenFrame() final override;

		// 閉じている
		void onCloseFrame() final override;

		//====================================================================================================
	public:
		ConfigPauseHowToPlay() {}
		~ConfigPauseHowToPlay() {}

		//====================================================================================================
		// メンバ関数

		// 描画優先度の設定
		void setRenderPriority(const float priority) final override;

		//====================================================================================================
	};

}
