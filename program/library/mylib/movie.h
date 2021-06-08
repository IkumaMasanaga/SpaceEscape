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
		// fromFlyWeightLoader, finalize‚ğŒÄ‚Ô‚½‚ß
		friend class t2k::SharedFlyweightMapInterface<std::string, Movie>;

		//====================================================================================================
		// ƒƒ“ƒo•Ï”
		int image_ = 0;
		int width_ = 0;
		int height_ = 0;
		std::string file_path_;

		//====================================================================================================
		// ƒƒ“ƒoŠÖ”
		void finalize() final override;

		//====================================================================================================
		// staticŠÖ”
		static Movie::SharedPtr fromFlyWeightLoader(const std::string& file_name, const std::string& file_path);

	public:
		Movie() {}
		~Movie() {}

		//====================================================================================================
		// ƒƒ“ƒoŠÖ”
		inline int getImage() const { return image_; }
		inline int getWidth() const { return width_; }
		inline int getHeight() const { return height_; }

		//====================================================================================================
		// staticŠÖ”
		static Movie::SharedPtr createFromFile(const std::string& file_path);
	};

}
