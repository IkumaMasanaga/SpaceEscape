#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class ConfigReset final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigReset>;
		using WeakPtr = std::weak_ptr<ConfigReset>;
	private:
		//====================================================================================================
		// メンバ定数

		// 選択項目
		inline static const int SELECT_YES = 0;
		inline static const int SELECT_NO = 1;

		//====================================================================================================
		// メンバ変数

		// メインの表示テキスト
		dxe::Text::SharedPtr main_text_ = nullptr;

		// 選択項目
		std::vector<dxe::Text::SharedPtr> select_texts_;

		// 選択項目
		int select_ = 1;

		// シーケンス処理用
		t2k::Sequence<ConfigReset*> seq_ = t2k::Sequence<ConfigReset*>(this, &ConfigReset::seqGuide);

		//====================================================================================================
		// メンバ関数

		// 派生先の生成時
		void onCreatedOfMainFrame() final override;

		// 開いているとき
		void onOpenFrame() final override;

		// 閉じているとき
		void onCloseFrame() final override;

		// 案内
		bool seqGuide();

		// 実行
		bool seqExecution();

		//====================================================================================================
	public:
		ConfigReset() {}
		~ConfigReset() {}

		//====================================================================================================
		// メンバ関数

		// 描画優先度の設定
		void setRenderPriority(const float priority) final override;

		//====================================================================================================
	};

}
