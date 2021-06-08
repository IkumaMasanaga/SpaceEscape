#include "DxLib.h"
#include "dx_main.h"
#include "../library/input.h"
#include "../library/mylib/time.h"
#include "../support/FrameRateController.h"
#include "../engine/dx_engine.h"
#include "../game/scene/logo.h"
#include "../game/save_data.h"


namespace sys {

	int DxMain::update() {

		const int WINDOW_WIDTH = 1024;
		const int WINDOW_HEIGHT = 768;
		const std::string WINDOW_NAME = "SPACE ESCAPE ～太陽系から脱出せよ！～";
		const std::string FONT_PATH = "font/PixelMplus12-Regular.ttf";
		const std::string FONT_NAME = "PixelMplus12";

		// フォントリソースの追加
		AddFontResourceEx(FONT_PATH.c_str(), FR_PRIVATE, NULL);
		ChangeFont(FONT_NAME.c_str(), DX_CHARSET_DEFAULT);
		ChangeFontType(DX_FONTTYPE_EDGE);

		// Windowの左上に出てくる名前変更
		SetWindowText(WINDOW_NAME.c_str());

		// アイコンの設定
		SetWindowIconID(111);

		// Log.txtを出力しない
		SetOutApplicationLogValidFlag(FALSE);

		// ウィンドウモードで起動
		ChangeWindowMode(true);

		// ウィンドウサイズ設定
		SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

		// ウィンドウが非アクティブ時でも処理を止めないようにする
		SetAlwaysRunFlag(true);

		// フレームレート設定
		FpsSetting(60, 800);

		// DXライブラリ初期化処理
		// エラーが起きたら直ちに終了
		if (DxLib_Init() == -1) return -1;

		// 描画先を裏画面に変更
		SetDrawScreen(DX_SCREEN_BACK);

		// 時間制御の初期化
		mylib::Time::initialize();

		// キー入力制御の初期化
		t2k::Input::initialize();

		// エンジンの初期化
		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		engine.initialize(WINDOW_WIDTH, WINDOW_HEIGHT, dxe::Scene::create<spe::Logo>());

		// セーブデータの読み込み
		spe::SaveData& save_data = spe::SaveData::getInstance();
		save_data.initialize();

		// サウンドマネージャー
		dxe::BGMManager& bgm_manager = dxe::BGMManager::getInstance();
		dxe::SEManager& se_manager = dxe::SEManager::getInstance();

		// 画面が有効になって最初のフレームか
		bool is_active_first_frame = false;

		// メッセージループ
		while (engine.is_playing_game_) {

			// 時間制御更新
			mylib::Time::update();

			// 毎フレーム呼ぶ
			if (ProcessMessage() == -1) break;

			// ウィンドウが非アクティブの場合はエンジンの更新を行わない
			if (GetWindowActiveFlag() == false) {
				bgm_manager.stop();
				se_manager.stop();
				is_active_first_frame = true;
				continue;
			}

			// 画面が有効になったら一時停止していたサウンドを再生する
			if (is_active_first_frame) {
				bgm_manager.playBackAll();
				se_manager.playBackAll();
				is_active_first_frame = false;
			}

			// 画面をクリア
			ClearDrawScreen();

			// キー状態の更新
			t2k::Input::update();

			// エンジンの更新
			engine.update();

			// フレームレートコントロール
			FpsControll();

			// バックバッファをフリップ
			ScreenFlip();
			//SetWaitVSyncFlag(FALSE);
		}

		// セーブデータの書き込み
		save_data.finalize();

		// エンジンの終了処理
		engine.finalize();
		dxe::DxEngine::destroy();

		// フォントリソースの解放
		RemoveFontResourceEx(FONT_PATH.c_str(), FR_PRIVATE, NULL);

		// DXライブラリ使用の終了処理
		DxLib_End();

		// ソフトの終了
		return 0;

	}

}
