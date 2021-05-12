#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class MessageWindow;
	class ConfigMenu;
	class ConfigPauseHowToPlay;
	class ConfigItem;
	class ConfigEnding;
	class ConfigRanking;
	class ConfigPauseVolume;
	class ConfigReset;

	class Config final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Config>;
		using WeakPtr = std::weak_ptr<Config>;
	private:
		//====================================================================================================
		// メンバ定数

		// メニューの座標
		inline static const t2k::Vector3 MENU_FRAME_POSITION = t2k::Vector3(-354.0f, -80.0f, 0.0f);

		// メインフレームの座標
		inline static const t2k::Vector3 MAIN_FRAME_POSITION = t2k::Vector3(140.0f, -80.0f, 0.0f);

		//====================================================================================================
		// メンバ変数

		t2k::Sequence<Config*> seq_ = t2k::Sequence<Config*>(this, &Config::seqMenu);

		// メッセージウィンドウ
		std::shared_ptr<MessageWindow> message_window_ = nullptr;

		// メニュー
		std::shared_ptr<ConfigMenu> menu_frame_ = nullptr;

		// 操作方法
		std::shared_ptr<ConfigPauseHowToPlay> how_to_play_ = nullptr;

		// アイテム
		std::shared_ptr<ConfigItem> item_ = nullptr;

		// エンディング
		std::shared_ptr<ConfigEnding> ending_ = nullptr;

		// ランキング
		std::shared_ptr<ConfigRanking> ranking_ = nullptr;

		// ボリューム
		std::shared_ptr<ConfigPauseVolume> volume_ = nullptr;

		// リセット
		std::shared_ptr<ConfigReset> reset_ = nullptr;

		//====================================================================================================
		// メンバ関数

		// 初期化
		void initialize() final override;

		// 更新
		void lateUpdate() final override;

		// 終了処理
		void finalize() final override;

		// メニュー
		bool seqMenu();

		// 操作説明
		bool seqHowToPlay();

		// アイテム
		bool seqItem();

		// エンディング
		bool seqEnding();

		// ランキング
		bool seqRanking();

		// ボリューム
		bool seqVolume();

		// リセット
		bool seqReset();

		//====================================================================================================
	public:
		Config() {}
		~Config() {}
	};

}
