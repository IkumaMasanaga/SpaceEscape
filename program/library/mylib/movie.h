#pragma once
#include <string>
#include "../shared_factory.h"
#include "../shared_flyweight_map.h"


namespace mylib {

	class Movie final : public t2k::SharedFactory<Movie>, public t2k::SharedFlyweightMapInterface<std::string, Movie> {
	public:
		using SharedPtr = std::shared_ptr<Movie>;
		using WeakPtr = std::weak_ptr<Movie>;
	private:
		// fromFlyWeightLoader, finalizeを呼ぶため
		friend class t2k::SharedFlyweightMapInterface<std::string, Movie>;

		//====================================================================================================
		// メンバ変数
		int image_ = 0;
		int width_ = 0;
		int height_ = 0;
		std::string file_path_;

		//====================================================================================================
		// メンバ関数
		void finalize() final override;

		//====================================================================================================
		// static関数
		static Movie::SharedPtr fromFlyWeightLoader(const std::string& file_name, const std::string& file_path);

	public:
		Movie() {}
		~Movie() {}

		//====================================================================================================
		// メンバ関数
		inline int getImage() const { return image_; }
		inline int getWidth() const { return width_; }
		inline int getHeight() const { return height_; }

		//====================================================================================================
		// static関数
		static Movie::SharedPtr createFromFile(const std::string& file_path);
	};

}
