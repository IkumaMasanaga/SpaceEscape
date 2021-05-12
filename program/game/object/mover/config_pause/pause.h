#pragma once
#include "../../../../engine/dxe.h"


namespace spe {

	class MessageWindow;
	class PauseMenu;
	class ConfigPauseHowToPlay;
	class PauseItem;
	class ConfigPauseVolume;
	class PauseTitle;

	class Pause final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<Pause>;
		using WeakPtr = std::weak_ptr<Pause>;
	private:
		//====================================================================================================
		// メンバ定数

		// 描画優先度
		inline static const float PRIORITY = 100.0f;

		// メニューの座標
		inline static const t2k::Vector3 MENU_FRAME_POSITION = t2k::Vector3(-354.0f, -80.0f, 0.0f);

		// メインフレームの座標
		inline static const t2k::Vector3 MAIN_FRAME_POSITION = t2k::Vector3(140.0f, -80.0f, 0.0f);

		//====================================================================================================
		// メンバ変数

		// シーケンス処理用
		t2k::Sequence<Pause*> seq_ = t2k::Sequence<Pause*>(this, &Pause::seqMenu);

		// メッセージウィンドウ
		std::shared_ptr<MessageWindow> message_window_ = nullptr;

		// メニュー
		std::shared_ptr<PauseMenu> menu_frame_ = nullptr;

		// 操作方法
		std::shared_ptr<ConfigPauseHowToPlay> how_to_play_ = nullptr;

		// アイテム
		std::shared_ptr<PauseItem> item_ = nullptr;

		// ボリューム
		std::shared_ptr<ConfigPauseVolume> volume_ = nullptr;

		// タイトルへ
		std::shared_ptr<PauseTitle> title_ = nullptr;

		// ポーズ終了フラグ
		bool is_end_ = false;

		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreated() final override;

		// 更新
		void update() final override;

		// メイン
		bool seqMenu();

		// 操作説明
		bool seqHowToPlay();

		// 獲得済アイテム
		bool seqItems();

		// ボリュームメイン
		bool seqVolume();

		// タイトル
		bool seqTitle();

		// 空いているフレームをすべて閉じる
		void closeFrames();

		//====================================================================================================
	public:
		Pause() {}
		~Pause() {}

		//====================================================================================================
		// メンバ関数

		// タイトルへ進むか
		bool toTitle() const;

		// ポーズ終了か
		inline bool isEnd() const { return is_end_; }

		//====================================================================================================
	};

}
