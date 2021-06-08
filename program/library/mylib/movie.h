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
		// fromFlyWeightLoader, finalize���ĂԂ���
		friend class t2k::SharedFlyweightMapInterface<std::string, Movie>;

		//====================================================================================================
		// �����o�ϐ�
		int image_ = 0;
		int width_ = 0;
		int height_ = 0;
		std::string file_path_;

		//====================================================================================================
		// �����o�֐�
		void finalize() final override;

		//====================================================================================================
		// static�֐�
		static Movie::SharedPtr fromFlyWeightLoader(const std::string& file_name, const std::string& file_path);

	public:
		Movie() {}
		~Movie() {}

		//====================================================================================================
		// �����o�֐�
		inline int getImage() const { return image_; }
		inline int getWidth() const { return width_; }
		inline int getHeight() const { return height_; }

		//====================================================================================================
		// static�֐�
		static Movie::SharedPtr createFromFile(const std::string& file_path);
	};

}
