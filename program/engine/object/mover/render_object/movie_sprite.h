#pragma once
#include "render_object.h"


namespace dxe {

	class MovieSprite final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<MovieSprite>;
		using WeakPtr = std::weak_ptr<MovieSprite>;
	private:
		//====================================================================================================
		// メンバ変数

		// 動画
		t2k::Movie::SharedPtr movie_ = nullptr;

		// ボリューム
		float volume_ = 1.0f;

		//====================================================================================================
		// メンバ関数

		// 描画
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		MovieSprite() {}
		~MovieSprite() {}

		//====================================================================================================
		// メンバ変数

		// x軸を基準に反転させるフラグ
		bool is_flip_x_ = false;

		// y軸を基準に反転させるフラグ
		bool is_flip_y_ = false;

		//====================================================================================================
		// メンバ関数

		// ボリュームの変更
		void setVolume(float volume);

		// 再生
		void play(bool is_seek_top = true);

		// 停止
		void stop();

		// 再生中か
		bool isPlaying();
		
		//====================================================================================================
		// static関数

		// リソースファイルから生成
		static MovieSprite::SharedPtr createFromFile(const std::string& file_path);

		//====================================================================================================
	};

}
