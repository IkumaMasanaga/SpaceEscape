#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	// 生成構造体
	struct OneShotAnimationDesc {
		std::string file_path_ = "";	// 画像のファイルパス
		int all_num_ = 0;				// 分割した際の総数
		int x_num_ = 0;					// 横方向の分割数
		int y_num_ = 0;					// 縦方向の分割数
		int width_ = 0;					// 1枚当たりの幅
		int height_ = 0;				// 1枚当たりの高さ

		float alive_time_ = 1.0f;		// 生存時間

		t2k::Vector3 start_position_ = t2k::Vector3::ZERO;	// 初期座標
		float start_rotation_ = 0.0f;						// 初期回転
		float start_scale_ = 1.0f;							// 初期スケール
		float start_alpha_ = 1.0f;							// 初期アルファ値
		t2k::Vector3 move_direction_ = t2k::Vector3::ZERO;	// 移動ベクトル
		float speed_per_second_ = 0.0f;						// 時間当たりの移動速度
		float angle_per_second_ = 0.0f;						// 時間当たりの回転角度
		float complete_scale_ = 1.0f;						// 消えるときのスケール
		float complete_alpha_ = 1.0f;						// 消えるときのアルファ値
		float render_priority_ = 0.0f;						// 描画優先度
		bool is_flip_x_ = false;							// x軸を基準に反転させるか
		bool is_flip_y_ = false;							// y軸を基準に反転させるか
	};

	class OneShotAnimation final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<OneShotAnimation>;
		using WeakPtr = std::weak_ptr<OneShotAnimation>;
	private:
		//====================================================================================================
		// メンバ変数

		// アニメーション
		dxe::AnimationSprite::SharedPtr animation_ = nullptr;

		// 時間当たりの回転角（ラジアン）
		float angle_per_second_ = 0.0f;

		// 移動ベクトル
		t2k::Vector3 move_ = t2k::Vector3::ZERO;

		// スケールの制御用
		t2k::TimerFluct<float> scale_controller_;

		// アルファ値の制御用
		t2k::TimerFluct<float> alpha_controller_;

		//====================================================================================================
		// メンバ関数

		void update() final override;

		//====================================================================================================
	public:
		OneShotAnimation() {}
		~OneShotAnimation() {}

		//====================================================================================================
		// static関数

		// 生成
		static OneShotAnimation::SharedPtr create(const OneShotAnimationDesc& desc);

		//====================================================================================================
	};

}
