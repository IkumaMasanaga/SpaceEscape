#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class VolumeSlider;

	class ConfigPauseVolume final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigPauseVolume>;
		using WeakPtr = std::weak_ptr<ConfigPauseVolume>;
	private:
		//====================================================================================================
		// メンバ定数

		// 選択項目
		inline static const int SELECT_BGM = 0;
		inline static const int SELECT_SE = 1;

		//====================================================================================================
		// メンバ変数

		// シーケンス
		t2k::Sequence<ConfigPauseVolume*> seq_ = t2k::Sequence<ConfigPauseVolume*>(this, &ConfigPauseVolume::seqMenu);

		// BGM用スライダー
		std::shared_ptr<VolumeSlider> bgm_slider_ = nullptr;

		// SE用スライダー
		std::shared_ptr<VolumeSlider> se_slider_ = nullptr;

		// テキスト
		std::vector<dxe::Text::SharedPtr> texts_;

		// 選択項目
		int select_ = 0;

		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreatedOfMainFrame() final override;

		// 開いているとき
		void onOpenFrame() final override;

		// 閉じているとき
		void onCloseFrame() final override;

		// 選択
		bool seqMenu();

		// BGM調整
		bool seqBGM();

		// SE調整
		bool seqSE();

		//====================================================================================================
	public:
		ConfigPauseVolume() {}
		~ConfigPauseVolume() {}

		//====================================================================================================

		// 描画優先度の設定
		void setRenderPriority(const float priority) final override;

		//====================================================================================================
	};

}
