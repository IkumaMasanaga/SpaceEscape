#pragma once
#include "../../../engine/dxe.h"
#include "../mover/one_shot_animation.h"


namespace spe {

	enum class EndType;

	class PlanetPlayer final : public dxe::PhysicsObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetPlayer>;
		using WeakPtr = std::weak_ptr<PlanetPlayer>;
	private:
		//====================================================================================================
		// メンバ定数

		// 前フレームでの補正方向フラグ
		inline static const int CORRECT_UP = 1 << 0;
		inline static const int CORRECT_DOWN = 1 << 1;
		inline static const int CORRECT_LEFT = 1 << 2;
		inline static const int CORRECT_RIGHT = 1 << 3;

		// 1個のエネルギーで回復する値
		inline static const float ENERGY_RECOVER_VALUE = 5.0f;

		//====================================================================================================
		// メンバ変数

		// 画像
		dxe::AnimationSprite::SharedPtr animation_ = nullptr;

		// アニメーションの時間
		std::unordered_map<std::string, float> animation_time_;

		// タックル時のトリガー衝突判定
		dxe::CollisionRect::SharedPtr tackle_rect_ = nullptr;

		// 移動力
		float move_power_ = 0.0f;

		// 通常時の移動力
		float default_move_power_ = 0.0f;

		// 空中での移動力
		float air_move_power_ = 0.0f;

		// タックル時の移動力の割合
		float tackle_move_rate_ = 1.0f;

		// タックル時フラグ
		bool is_tackle_ = false;

		// ジャンプ力
		float jump_power_ = 0.0f;

		// 通常時の摩擦力
		t2k::Vector3 default_friction_ = t2k::Vector3::ZERO;

		// 攻撃時の摩擦力
		t2k::Vector3 attack_friction_ = t2k::Vector3::ZERO;

		// 補正フラグ
		int correct_flag_ = 0;

		// ジャンプ可能か
		bool can_jump_ = false;

		// ダメージを受けた際の時間経過
		float damage_time_count_ = 0.0f;

		// 点滅用
		float flash_time_count_ = 0.0f;

		// 攻撃を受けたか
		bool is_damage_ = false;

		// キーアイテムを獲得したか
		bool is_get_key_item_ = false;

		// 死亡時のエンディングタイプ
		EndType end_type_ = (EndType)0;

		// タックルを溜めている時のエフェクトの時間
		float effect_time_tackle_charge_ = 0.0f;

		// タックルを溜めきった時のエフェクトの時間
		float effect_time_tackle_charge_max_ = 0.0f;

		// タックルチャージ中エフェクト
		OneShotAnimationDesc tackle_charge_desc_;

		// タックルエフェクト
		OneShotAnimationDesc tackle_desc_;
		OneShotAnimation::WeakPtr effect_tackle_;

		// エネルギー獲得エフェクト
		OneShotAnimationDesc energy_desc_;

		// 煙エフェクト
		OneShotAnimationDesc smoke_desc_;
		OneShotAnimation::WeakPtr effect_smoke_;

		// 軌跡生成用カウンタ
		float generate_locus_time_count_ = 0.0f;

		// タックル時のSE呼び出し用カウンタ
		float tackle_se_count_ = 0.0f;

		// 軌跡エフェクト
		OneShotAnimationDesc locus_desc_;

		// 軌跡画像のファイルパス
		std::vector<std::string> locus_file_paths_;

		// シーケンス処理用
		t2k::Sequence<PlanetPlayer*> seq_ = t2k::Sequence<PlanetPlayer*>(this, &PlanetPlayer::seqIdle);

		//====================================================================================================
		// メンバ関数
		
		// 生成時
		void onCreated() final override;

		// 更新
		void update() final override;

		// 衝突時
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;
		
		// 待機シーケンス
		bool seqIdle();

		// 攻撃シーケンス
		bool seqAttack();

		// タックルチャージシーケンス
		bool seqEnergyActionCharge();

		// タックル実行シーケンス
		bool seqEnergyActionAttack();

		// ダメージ受けた時シーケンス
		bool seqDamage();

		// 死亡時シーケンス
		bool seqDeath();

		// ダメージによる点滅
		void flashByDamage();

		//====================================================================================================
	public:
		PlanetPlayer() {}
		~PlanetPlayer() {}

		//====================================================================================================
		// メンバ関数

		// キーアイテムを獲得したかの設定
		inline void setGetKeyItem(const bool is_get_key_item) { is_get_key_item_ = is_get_key_item; }

		// キーアイテムを獲得したか
		inline bool isGetKeyItem() const { return is_get_key_item_; }

		//====================================================================================================
	};

}
