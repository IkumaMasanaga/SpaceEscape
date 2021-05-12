#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class PauseTitle final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<PauseTitle>;
		using WeakPtr = std::weak_ptr<PauseTitle>;
	private:
		//====================================================================================================
		// メンバ定数

		// 選択項目
		inline static const int SELECT_YES = 0;
		inline static const int SELECT_NO = 1;

		//====================================================================================================
		// メンバ変数

		// 選択項目
		std::vector<dxe::Text::SharedPtr> select_texts_;

		// 描画優先度の設定をするための管理用リスト
		std::list<dxe::Text::SharedPtr> texts_;

		// 選択項目
		int select_ = 1;

		// タイトルへフラグ
		bool to_title_ = false;

		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreatedOfMainFrame() final override;

		// 開いているとき
		void onOpenFrame() final override;

		// 閉じているとき
		void onCloseFrame() final override;

		//====================================================================================================
	public:
		PauseTitle() {}
		~PauseTitle() {}

		//====================================================================================================
		// メンバ関数

		// 描画優先度の設定
		void setRenderPriority(const float priority) final override;

		// タイトルへフラグの取得
		inline bool toTitle() const { return to_title_; }

		//====================================================================================================
	};

}
