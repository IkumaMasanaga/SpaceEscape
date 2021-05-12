#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class MessageWindow;

	class Prologue final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Prologue>;
		using WeakPtr = std::weak_ptr<Prologue>;
	private:
		//====================================================================================================
		// メンバ関数
		
		// メッセージウィンドウ
		std::shared_ptr<MessageWindow> message_window_ = nullptr;
		
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
		Prologue() {}
		~Prologue() {}
	};

}
