#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	// 生成構造体
	struct BackgroundStarsDesc final {
		int width_ = 0;				// 生成幅
		int height_ = 0;			// 生成高さ
		int generate_num_ = 100;	// 生成数
		float render_position_from_camera_ = 0.5f;	// カメラからの距離
		float animation_time_min_ = 0.5f;			// 最小アニメーション完了時間
		float animation_time_max_ = 1.5f;			// 最大アニメーション完了時間
		float scale_min_ = 0.5f;	// 最小拡大率
		float scale_max_ = 2.0f;	// 最大拡大率
		float priority_ = -1.0f;	// 描画優先度
	};

	// 背景の星
	// AnimationSpriteで1つ1つ生成するより軽いが、各Spriteでアニメーション間隔は同じ、アルファ値も同じ
	class BackgroundStars final : public dxe::RenderObject {
	public:
		using SharedPtr = std::shared_ptr<BackgroundStars>;
		using WeakPtr = std::weak_ptr<BackgroundStars>;
	private:
		//====================================================================================================
		// インナークラス

		struct BackgroundStar final {
			t2k::Transform transform_;
			int sprite_id_ = 0;
		};

		struct StarSprite final {
			std::vector<t2k::Texture::SharedPtr> textures_;
			int animation_index_ = 0;
			t2k::TimerFluct<int> animation_;
			float complete_time_ = 0.0f;
		};

		//====================================================================================================
		// メンバ変数

		// 描画位置とid
		std::vector<BackgroundStar> stars_;

		// 画像の種類とアニメーション
		std::vector<StarSprite> star_sprites_;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update() final override;

		// 描画
		void render(std::shared_ptr<dxe::Screen> screen) final override;

		//====================================================================================================
	public:
		BackgroundStars() {}
		~BackgroundStars() {}

		//====================================================================================================
		// static関数

		// 生成
		static BackgroundStars::SharedPtr create(const BackgroundStarsDesc& desc);

		//====================================================================================================
	};

}
