#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class SE;

	// SEの管理用キー
	enum class SEKey {
		ENTER,				// 決定
		SELECT,				// 選択
		BACK,				// 戻る
		JUMP,				// ジャンプ
		ATTACK,				// 攻撃
		DAMAGE,				// ダメージを受けた際
		WARP,				// ワープ
		ITEM,				// アイテム獲得
		HIT,				// 攻撃が当たった
		ENERGY,				// エネルギー獲得
		PAUSE,				// ポーズ
		JET,				// ジェット
		LIMIT,				// 残り時間30
		HIT2,				// 攻撃が弾かれた
		TACKLE,				// タックル実行
		SMOKE,				// 煙
		PREPARE_TACKLE_1,	// タックル溜め中
		PREPARE_TACKLE_2,	// タックル溜め完了
		WARNING,			// エネルギー残りわずか
	};

	// SE一括管理クラス
	// SEの登録
	// SEの再生
	// SEの停止
	// SEのボリューム調整
	class SEManager final : public mylib::Singleton<SEManager> {
	private:
		// 基底クラスで生成するため
		friend class mylib::Singleton<SEManager>;
		// releaceAllを呼ぶため
		friend class DxEngine;

		SEManager();

		//====================================================================================================
		// インナークラス

		// 登録する情報
		class SERegistData final {
		public:
			std::string file_path_;
			float volume_ = 1.0f;
			bool is_loop_ = false;
		};

		//====================================================================================================
		// メンバ変数

		// SE一括管理用連想配列
		std::unordered_map<SEKey, std::shared_ptr<SE>> se_map_;

		// 登録情報とキーを結びつける連想配列
		std::unordered_map<SEKey, SERegistData> regist_data_map_;

		// SE全体のボリューム
		float master_volume_ = 1.0f;

		//====================================================================================================
		// メンバ関数

		// 自身が管理しているSEを解放する
		void releaceAll();

		//====================================================================================================
	public:
		~SEManager() {}

		//====================================================================================================
		// メンバ関数

		// SE全体のボリュームを取得
		inline float getMasterVolume() const { return master_volume_; }
		
		// SE全体のボリュームを設定
		void setMasterVolume(const float master_volume);

		// SEの登録
		std::shared_ptr<SE> registSE(const SEKey key);

		// SEの取得
		std::shared_ptr<SE> getSE(const SEKey key) const;
		
		// SEの再生
		std::shared_ptr<SE> play(const SEKey key) const;

		// 一時停止中のSEの再生再開
		void playBackAll();

		// 再生中のSEの停止
		void stop() const;

		// SEの停止
		void stop(const SEKey key) const;

		// SEが再生中か
		bool isPlaying(const SEKey key) const;

		//====================================================================================================
	};

}
