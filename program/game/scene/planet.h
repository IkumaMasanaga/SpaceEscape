#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class MessageWindow;
	class Pause;
	class PlanetPlayer;
	class PlanetKeyItem;
	class PlanetKeyItemFrame;
	class PlanetWarpPoint;

	class Planet final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Planet>;
		using WeakPtr = std::weak_ptr<Planet>;
	private:
		//====================================================================================================
		// メンバ変数

		// 惑星番号
		int id_ = -1;

		// メッセージウィンドウ
		std::shared_ptr<MessageWindow> message_window_ = nullptr;

		// プレイヤー
		std::shared_ptr<PlanetPlayer> player_ = nullptr;

		// キーアイテム
		std::shared_ptr<PlanetKeyItem> key_item_ = nullptr;

		// キーアイテム獲得時のフレーム
		std::shared_ptr<PlanetKeyItemFrame> key_item_frame_ = nullptr;

		// キーアイテム獲得時のぼかし
		dxe::Sprite::SharedPtr blur_ = nullptr;

		// HP回復のテキスト
		dxe::Text::SharedPtr hp_text_ = nullptr;

		// 各惑星、宇宙へ行くポイント
		std::list<std::shared_ptr<PlanetWarpPoint>> warp_points_;

		// このシーンに遷移する前のシーンの情報
		std::string prev_scene_;

		// マップ、イベント、敵情報が入っているCSVフォルダのパス
		std::string csv_folder_path_;

		// シーケンス処理用
		t2k::Sequence<Planet*> seq_ = t2k::Sequence<Planet*>(this, &Planet::seqIdle);

		// ポーズ
		std::shared_ptr<Pause> pause_ = nullptr;

		//====================================================================================================
		// メンバ関数

		// 初期化
		void initialize() final override;

		// 更新
		void lateUpdate() final override;

		// 終了処理
		void finalize() final override;

		// 通常
		bool seqIdle();

		// キーアイテム獲得
		bool seqGetKeyItem();

		// ポーズシーケンス
		bool seqPause();

		//====================================================================================================
	public:
		Planet() {}
		~Planet() {}

		//====================================================================================================
		// static関数

		static Planet::SharedPtr create(const std::string& prev_scene, const std::string& csv_folder_path);

		//====================================================================================================
	};

}
