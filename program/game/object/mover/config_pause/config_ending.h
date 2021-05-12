#pragma once
#include "config_pause_main_frame.h"


namespace spe {

	class ConfigEnding final : public ConfigPauseMainFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigEnding>;
		using WeakPtr = std::weak_ptr<ConfigEnding>;
	private:
		//====================================================================================================
		// メンバ定数

		// 描画数
		inline static const int RENDER_NUM = 10;

		//====================================================================================================
		// メンバ変数

		// 描画するエンディング文字列のオブジェクト
		std::vector<dxe::Text::SharedPtr> render_endings_;

		// エンディング
		std::vector<std::string> endings_;

		// メッセージウィンドウに表示するテキストのファイルパス
		std::vector<std::string> message_file_path_;

		// 選択キーが押されたか
		bool is_key_pressed_select_ = false;

		// 選択中の項目
		int select_ = 0;

		// 描画開始する要素数
		int start_index_ = 0;

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
		ConfigEnding() {}
		~ConfigEnding() {}

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
