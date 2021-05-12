#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class Title final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Title>;
		using WeakPtr = std::weak_ptr<Title>;
	private:
		//====================================================================================================
		// メンバ定数

		// 選択項目の番号
		inline static const int SELECT_START = 0;
		inline static const int SELECT_CONFIG = 1;
		inline static const int SELECT_EXIT = 2;

		//====================================================================================================
		// メンバ変数

		// PRESS [ C ] TO START
		dxe::Text::SharedPtr press_c_ = nullptr;

		// 選択項目の親オブジェクト
		dxe::Mover::SharedPtr select_parent_ = nullptr;

		// 選択項目の色を変更するための配列
		std::vector<dxe::Text::SharedPtr> select_texts_;

		// 現在選択中の要素
		unsigned int selected_ = 0;

		// シーケンス処理用
		t2k::Sequence<Title*> seq_ = t2k::Sequence<Title*>(this, &Title::seqPressC);

		//====================================================================================================
		// メンバ関数

		// 初期化
		void initialize() final override;

		// 更新
		void lateUpdate() final override;

		// 終了処理
		void finalize() final override;
		
		// 最初のシーケンス
		bool seqPressC();

		// メニュー選択シーケンス
		bool seqSelectMenu();

		//====================================================================================================
	public:
		Title() {}
		~Title() {}
	};

}
