#pragma once
#include "../engine/dxe.h"
#include "../system/dx_main.h"


namespace spe {

	// 惑星番号
	enum class PlanetID {
		SUN,		// 太陽
		MERCURY,	// 水星
		VENUS,		// 金星
		EARTH,		// 地球
		MARS,		// 火星
		JUPITER,	// 木星
		SATURN,		// 土星
		URANUS,		// 天王星
		NEPTUNE,	// 海王星
		PLUTO		// 冥王星
	};

	// 分岐エンドの種類
	enum class EndType {
		BAD_TIME_UP,			// 太陽爆発エンド
		BAD_SUN_EXPLOSION,		// 太陽暴発エンド
		BAD_SUN_BURNING,		// 太陽灼熱エンド
		BAD_NEPTUNE_POISON,		// 海王星毒ガスエンド
		BAD_PLANET_ENEMY,		// 敵対生物エンド
		BAD_PLANET_FALLING,		// 惑星落下エンド
		BAD_PLANET_JUMP_OUT,	// 宇宙飛び出しエンド
		BAD_SPACE_ENERGY,		// 宇宙漂流エンド
		BAD_NEW_WORLD_POISON,	// 新惑星毒ガスエンド
		BAD_NEW_WORLD_BURNING,	// 新惑星灼熱エンド
		GOOD_NEW_WORLD,			// 新惑星快適エンド
		GOOD_SURVIVAL,			// 生還エンド
		TRUE_PLUTO,				// 夢オチエンド（冥王星）
	};

	class SaveData final : public t2k::Singleton<SaveData> {
	private:
		// 基底クラスで生成するため
		friend class t2k::Singleton<SaveData>;
		// initialize, finalizeを呼ぶため
		friend class sys::DxMain;

		SaveData() {}

		//====================================================================================================
		// メンバ変数

		// クリアしたことがあるエンディング
		int clear_ends_ = 0;

		// 獲得したことがあるアイテム
		int get_items_ = 0;

		// 新惑星快適エンドのランキング
		float good_new_world_ranking_[3] = { 0.0f };

		// 生還エンドのランキング
		float good_survival_ranking_[3] = { 0.0f };

		//====================================================================================================
		// メンバ関数

		// 初期化
		void initialize();

		// 終了処理
		void finalize();
	
		// GOODエンドのランキングを記録する
		float* recordGoodRanking(const EndType end_type, const float clear_time);

		// 外部ファイルに記録
		void save();

		// 外部ファイルから読み込み
		void load();

		//====================================================================================================
	public:
		~SaveData() {}

		//====================================================================================================
		// メンバ定数

		// 惑星数
		inline static const int PLANET_MAX = 10;

		// エンディングの数
		inline static const int ENDING_MAX = 13;

		//====================================================================================================
		// メンバ変数

		// BGMのマスターボリューム
		float bgm_volume_ = 0.8f;

		// SEのマスターボリューム
		float se_volume_ = 0.8f;

		//====================================================================================================
		// メンバ関数

		// クリアしたエンディングの記録
		inline void recordClearEnd(const EndType end_type) { clear_ends_ |= (1 << (int)end_type); }

		// エンディングをクリアしたか
		inline bool isClearEnd(const EndType end_type) const { return clear_ends_ & (1 << (int)end_type); }

		// 獲得したアイテムを記録
		inline void recordGetItems(const int get_items) { get_items_ |= get_items; }

		// アイテムを獲得したか
		inline bool hasItem(const PlanetID planet_id) const { return get_items_ & (1 << (int)planet_id); }

		// ランキングを記録し文字列オブジェクトを生成する
		dxe::Mover::SharedPtr createRankingText(const EndType end_type, const float clear_time);

		// ランキングの文字列オブジェクトを生成する
		dxe::Mover::SharedPtr createRankingText(const EndType end_type);

		// 外部ファイルに記録したデータをリセット
		void reset();

		// BGMマスターボリュームの変更
		void changeBGMVolume(const float change_value);

		// SEマスターボリュームの変更
		void changeSEVolume(const float change_value);

		//====================================================================================================
	};

}
