#pragma once
#include <string>
#include "shared_factory.h"
#include "shared_flyweight_map.h"

namespace t2k{

	class Texture final : public SharedFactory<Texture>, public SharedFlyweightMapInterface<std::string, Texture> {
	public:
		typedef std::shared_ptr<Texture> SharedPtr;
		typedef std::weak_ptr<Texture> WeakPtr;
	private:
		// fromFlyWeightLoader, finalizeを呼ぶため
		friend class SharedFlyweightMapInterface<std::string, Texture>;

		int image_ = 0;
		int size_w_ = 0;
		int size_h_ = 0;
		std::string file_path_;

		// SharedFlyWeightMap 用のローダー
		static Texture::SharedPtr fromFlyWeightLoader(const std::string& key, const std::string& file_name);

		// SharedFlyWeightMap 用の終了処理
		void finalize() final override;

	public:
		Texture() {}
		~Texture(){}

		inline int getImage() const { return image_; }
		inline int getWidth() const { return size_w_; }
		inline int getHeight() const { return size_h_; }

		// テクスチャから範囲を指定して新しいテクスチャを生成する
		Texture::SharedPtr partiallyCreatedFromTexture( const int src_left_up_x, const int src_left_up_y, const int width, const int height ) const;

		// 描画テクスチャの生成
		static Texture::SharedPtr createRenderTexture( const int width, const int height );

		// リソースファイルからテクスチャを生成
		static Texture::SharedPtr createFromFile(const std::string& file_path);

		// リソースファイルからテクスチャのvectorを生成
		static std::vector<Texture::SharedPtr> createVectorFromFile(const std::string& file_path, const int all_num, const int x_num, const int y_num, const int width, const int height);
	};

}
