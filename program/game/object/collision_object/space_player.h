#pragma once
#include "../../../engine/dxe.h"
#include "../mover/one_shot_animation.h"


namespace spe {

	class SpacePlayer final : public dxe::CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<SpacePlayer>;
		using WeakPtr = std::weak_ptr<SpacePlayer>;
	private:
		//====================================================================================================
		// メンバ定数

		// テクスチャ関係
		static const int TEXTURE_INDEX_NORMAL = 0;
		static const int TEXTURE_INDEX_DOWN = 1;
		static const int TEXTURE_INDEX_UP = 2;
		static const int TEXTURE_NUM = 3;

		//====================================================================================================
		// メンバ変数

		// テクスチャ
		t2k::Texture::SharedPtr textures_[TEXTURE_NUM];

		// 画像
		dxe::Sprite::SharedPtr sprite_;

		// 入力用
		bool up_ = false;
		bool down_ = false;
		bool left_ = false;
		bool right_ = false;

		// ジェットの生成用カウンタ
		float generate_jet_time_count_ = 0.0f;

		// ジェットの生成時間
		float generate_jet_time_ = 0.07f;

		// ジェットの生成構造体
		OneShotAnimationDesc jet_desc_;

		// 最高速度
		float speed_max_ = 0.0f;

		// スピードに対する消費エネルギーの割合
		float consume_energy_rate_ = 0.0f;

		// 慣性っぽい動き用（X軸）
		mylib::SmoothNormalize x_;

		// 慣性っぽい動き用（Y軸）
		mylib::SmoothNormalize y_;

		// 死亡フラグ
		bool is_dead_ = false;

		//====================================================================================================
		// メンバ関数

		// 生成時
		void onCreated() final override;

		// 更新
		void update() final override;

		// 衝突時
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		SpacePlayer() {}
		~SpacePlayer() {}

		//====================================================================================================
		// メンバ関数

		// 死亡フラグの取得
		inline bool isDead() const { return is_dead_; }

		//====================================================================================================
	};

}
