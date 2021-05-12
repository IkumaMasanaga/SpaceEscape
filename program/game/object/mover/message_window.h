#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class UIFrame;

	class MessageWindow final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<MessageWindow>;
		using WeakPtr = std::weak_ptr<MessageWindow>;
	private:
		//====================================================================================================
		// メンバ変数

		// 枠
		std::shared_ptr<UIFrame> frame_ = nullptr;

		// 文字
		dxe::Text::SharedPtr text_ = nullptr;

		// キーのアニメーション
		dxe::AnimationSprite::SharedPtr c_key_ = nullptr;

		// キー描画フラグ
		bool is_active_c_key_ = true;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update() final override;

		//====================================================================================================
	public:
		MessageWindow() {}
		~MessageWindow() {}

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

		// キーが有効か
		inline bool isActiveCKey() const { return is_active_c_key_; }

		// キー有効フラグの設定
		inline void setActiveCKey(const bool is_active) { is_active_c_key_ = is_active; }

		// 文字列の変更
		inline void changeText(const std::string& text) { text_->changeText(text); }

		// 外部ファイルから文字列の変更
		inline void changeTextFromFile(const std::string& file_path) { text_->changeTextFromFile(file_path); }

		//====================================================================================================
		// static関数

		// 生成
		static MessageWindow::SharedPtr create(const std::string& text);

		// 外部ファイルから文字列を設定して生成
		static MessageWindow::SharedPtr createFromFile(const std::string& file_path);

		//====================================================================================================
	};

}
