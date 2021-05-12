#pragma once
#include "render_object.h"


namespace dxe {

	class Sprite final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<Sprite>;
		using WeakPtr = std::weak_ptr<Sprite>;
	private:
		//====================================================================================================
		// メンバ変数

		// 描画テクスチャ
		t2k::Texture::SharedPtr texture_;

		//====================================================================================================
		// メンバ関数

		// 描画
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		Sprite() {}
		~Sprite() {}

		//====================================================================================================
		// メンバ変数

		// x軸を基準に反転させるフラグ
		bool is_flip_x_ = false;

		// y軸を基準に反転させるフラグ
		bool is_flip_y_ = false;

		//====================================================================================================
		// メンバ関数

		// テクスチャの取得（参照用）
		inline const t2k::Texture::SharedPtr getTexture() { return texture_; }

		// テクスチャの変更
		inline void changeTexture(const t2k::Texture::SharedPtr texture) { texture_ = texture; }

		//====================================================================================================
		// static関数

		// テクスチャから生成
		static Sprite::SharedPtr createFromTexture(t2k::Texture::SharedPtr texture);

		// リソースファイルから生成
		static Sprite::SharedPtr createFromFile(const std::string& file_path);

		//====================================================================================================
	};

}
