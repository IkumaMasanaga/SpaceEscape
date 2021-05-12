#pragma once
#include "../../engine/dxe.h"


namespace spe {

	enum class EndType;
	class MessageWindow;

	class Epilogue final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Epilogue>;
		using WeakPtr = std::weak_ptr<Epilogue>;
	private:
		//====================================================================================================
		// メンバ変数

		EndType end_type_ = (EndType)0;

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
		Epilogue() {}
		~Epilogue() {}

		//====================================================================================================
		// static関数

		// 生成
		static Epilogue::SharedPtr create(const EndType& end_type);

		//====================================================================================================
	};

}
