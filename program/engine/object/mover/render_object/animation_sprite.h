#pragma once
#include "render_object.h"


namespace dxe {

	class AnimationSprite final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<AnimationSprite>;
		using WeakPtr = std::weak_ptr<AnimationSprite>;
	private:
		//====================================================================================================
		// メンバ変数

		// 現在設定されているアニメーションの名前
		std::string now_name_ = "none_image";

		// 現在設定されているアニメーションの画像
		std::vector<t2k::Texture::SharedPtr> now_textures_;

		// アニメーションのループフラグ
		bool is_loop_ = false;

		// 現在のアニメーションのコマ数
		int now_index_ = 0;

		// アニメーション完了時間
		float complete_time_ = 0.0f;

		// アニメーション実行用
		t2k::TimerFluct<int> animation_;

		// アニメーション管理連想配列
		std::unordered_map<std::string, std::vector<t2k::Texture::SharedPtr>> register_textures_;

		//====================================================================================================
		// メンバ関数

		void update() final override;

		// 描画
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		AnimationSprite() {}
		~AnimationSprite() {}

		//====================================================================================================
		// メンバ変数

		// x軸を基準に反転させるフラグ
		bool is_flip_x_ = false;

		// y軸を基準に反転させるフラグ
		bool is_flip_y_ = false;

		//====================================================================================================
		// メンバ関数

		// アニメーションの登録
		void registAnimation(const std::string& animation_name, const std::vector<t2k::Texture::SharedPtr>& textures);

		// アニメーションの再生
		void play(const std::string& animation_name, const float complete_time, const bool is_loop);

		// 現在再生中のアニメーションの名前の取得
		inline std::string getNowAnimationName() const { return now_name_; }

		// アニメーション再生中か
		inline bool isPlaying() const { return is_loop_ || !animation_.isComplete(); }

		//====================================================================================================

	};

}
