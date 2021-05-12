#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class ConfigItem final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigItem>;
		using WeakPtr = std::weak_ptr<ConfigItem>;
	private:
		//====================================================================================================
		// メンバ変数

		// アイテム
		std::vector<dxe::Text::SharedPtr> items_;

		// メッセージウィンドウに表示するテキストのファイルパス
		std::vector<std::string> message_file_path_;

		// 選択キーが押されたか
		bool is_key_pressed_select_ = false;

		// 選択中の項目
		int select_ = 0;

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
		ConfigItem() {}
		~ConfigItem() {}

		//====================================================================================================
		// メンバ関数

		// 描画優先度の設定
		void setRenderPriority(const float priority) final override;

		// 選択キーが押されたか
		inline bool isKeyPressedSelect() const { return is_key_pressed_select_; }

		// 選択中の項目のメッセージウィンドウのテキストファイルパスの取得
		inline std::string getMessageTextFilePath() const { return message_file_path_[select_]; }

		//====================================================================================================
	};

}
