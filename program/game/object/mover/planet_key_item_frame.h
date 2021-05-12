#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class UIFrame;

	class PlanetKeyItemFrame final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<PlanetKeyItemFrame>;
		using WeakPtr = std::weak_ptr<PlanetKeyItemFrame>;
	private:
		//====================================================================================================
		// メンバ変数

		// 枠
		std::shared_ptr<UIFrame> frame_ = nullptr;

		// キーアイテム画像
		dxe::Sprite::SharedPtr key_item_ = nullptr;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update() final override;

		//====================================================================================================
	public:
		PlanetKeyItemFrame() {}
		~PlanetKeyItemFrame() {}

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

		//====================================================================================================
		// static関数

		// 生成
		static PlanetKeyItemFrame::SharedPtr create(const std::string file_path);

		//====================================================================================================
	};

}
