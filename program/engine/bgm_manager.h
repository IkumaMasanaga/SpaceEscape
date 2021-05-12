#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class BGM;

	// BGMの管理用キー
	enum class BGMKey {
		TITLE,				// タイトル
		CONFIG,				// コンフィグ
		PROLOGUE,			// プロローグ
		PLAY1,				// プレイ中
		PLAY2,				// プレイ中（残り時間少ない）
		EPILOGUE_CLEAR,		// エピローグ（クリア）
		EPILOGUE_GAME_OVER,	// エピローグ（ゲームオーバー）
	};

	// BGM一括管理クラス
	// BGMの登録
	// BGMの再生
	// BGMの停止
	// BGMのボリューム調整
	class BGMManager final : public t2k::Singleton<BGMManager> {
	private:
		// 基底クラスで生成するため
		friend class t2k::Singleton<BGMManager>;
		// releaceAllを呼ぶため
		friend class DxEngine;

		BGMManager();

		//====================================================================================================
		// インナークラス

		// 登録する情報
		class BGMRegistData final {
		public:
			std::string file_path_;
			float volume_ = 1.0f;
			bool is_loop_ = true;
		};

		//====================================================================================================
		// メンバ変数

		// BGM一括管理用連想配列
		std::unordered_map<BGMKey, std::shared_ptr<BGM>> bgm_map_;

		// 登録情報とキーを結びつける連想配列
		std::unordered_map<BGMKey, BGMRegistData> regist_data_map_;

		// BGM全体のボリューム
		float master_volume_ = 1.0f;

		//====================================================================================================
		// メンバ関数

		// 自身が管理しているBGMを解放する
		void releaceAll();

		//====================================================================================================
	public:
		~BGMManager() {}

		//====================================================================================================
		// メンバ関数

		// BGM全体のボリュームを取得
		inline float getMasterVolume() const { return master_volume_; }

		// BGM全体のボリュームを取得
		void setMasterVolume(const float master_volume);

		// BGMの登録
		std::shared_ptr<BGM> registBGM(const BGMKey key);

		// BGMの取得
		std::shared_ptr<BGM> getBGM(const BGMKey key) const;

		// BGMの再生
		// 第二引数に true を設定すると今再生中のBGMを止めずに重ねて再生する
		std::shared_ptr<BGM> play(const BGMKey key, const bool is_duplicate = false) const;
		
		// 一時停止中のSEの再生再開
		void playBackAll();

		// 再生中のBGMの停止
		void stop() const;
		
		// BGMの停止
		void stop(const BGMKey key) const;

		// BGMが再生中か
		bool isPlaying(const BGMKey key) const;

		//====================================================================================================
	};

}
