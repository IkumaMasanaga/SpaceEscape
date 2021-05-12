#pragma once
#include "../../../../engine/dxe.h"


namespace spe {

	class UIFrame;

	class ConfigPauseMenuFrame : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<ConfigPauseMenuFrame>;
		using WeakPtr = std::weak_ptr<ConfigPauseMenuFrame>;
	private:
		//====================================================================================================
		// メンバ変数

		// 枠
		std::shared_ptr<UIFrame> frame_ = nullptr;

		// 選択キーが押されたか
		bool is_key_pressed_select_ = false;

		// 選択中の項目
		int select_ = 0;

		//====================================================================================================
		// メンバ関数

		// 派生先の生成時
		virtual void onCreatedOfMenuFrame() = 0;

		// 生成時
		void onCreated() final override;

		// 更新
		void update() final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// メンバ変数

		// メニュー項目
		std::vector<dxe::Text::SharedPtr> texts_;

		// メッセージウィンドウに表示するテキストのファイルパス
		std::vector<std::string> message_file_path_;

		//====================================================================================================
	public:
		ConfigPauseMenuFrame() {}
		virtual ~ConfigPauseMenuFrame() {}

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

		// 選択キーが押されたか
		inline bool isKeyPressedSelect() const { return is_key_pressed_select_; }

		// 選択中の項目のメッセージウィンドウのテキストファイルパスの取得
		inline std::string getMessageTextFilePath() const { return message_file_path_[select_]; }

		// 選択中の項目を取得
		inline int getSelectIndex() const { return select_; }

		//====================================================================================================
	};

}
