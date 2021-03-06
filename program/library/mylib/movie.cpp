#include "DxLib.h"
#include "../util.h"
#include "movie.h"


namespace mylib {

	Movie::SharedPtr Movie::fromFlyWeightLoader(const std::string& file_name, const std::string& file_path) {
		Movie::SharedPtr ptr = SharedFactory::create<Movie>();
		ptr->file_path_ = file_name;
		ptr->image_ = LoadGraph(file_path.c_str());
		if (-1 != ptr->image_) return ptr;
		warningMassage(("動画のロードに失敗 : " + file_path).c_str());
		return nullptr;
	}

	void Movie::finalize() {
		DeleteGraph(image_);
	}

	Movie::SharedPtr Movie::createFromFile(const std::string& file_path) {
		return flyweight_map_.load(file_path, file_path);
	}

}
