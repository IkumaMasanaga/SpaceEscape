#pragma once
#include "../../../../engine/dxe.h"


namespace spe {

	class UIFrame;

	class ConfigPauseMainFrame : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<ConfigPauseMainFrame>;
		using WeakPtr = std::weak_ptr<ConfigPauseMainFrame>;
	private:
		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreated() final override;

		// 更新
		void update() final override;

		//====================================================================================================
	protected:
		//====================================================================================================
		// メンバ変数

		// 枠
		std::shared_ptr<UIFrame> frame_ = nullptr;

		//====================================================================================================
		// メンバ関数

		// 派生先の生成時
		virtual void onCreatedOfMainFrame() = 0;

		// 開いているときの処理
		virtual void onOpenFrame() = 0;

		// 閉じているとき（空いていない時）の処理
		// 閉じる、開く途中も実行される
		virtual void onCloseFrame() = 0;

		//====================================================================================================
	public:
		ConfigPauseMainFrame() {}
		virtual ~ConfigPauseMainFrame() {}

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

		// 描画優先度の設定
		virtual void setRenderPriority(const float priority) = 0;

		//====================================================================================================
	};

}
