#include "wrap.h"
#include "util.h"
#include "texture.h"

namespace t2k{

	Texture::SharedPtr Texture::partiallyCreatedFromTexture(const int src_left_up_x, const int src_left_up_y, const int width, const int height) const {
		Texture::SharedPtr ptr = SharedFactory::create<Texture>();
		ptr->image_ = DerivationGraph(src_left_up_x, src_left_up_y, width, height, image_);
		ptr->size_w_ = width;
		ptr->size_h_ = height;
		ptr->file_path_ = file_path_;
		return ptr;
	}

	Texture::SharedPtr Texture::createRenderTexture(const int width, const int height) {
		Texture::SharedPtr ptr = SharedFactory::create<Texture>();
		SetDrawValidGraphCreateFlag(TRUE);
		ptr->image_ = MakeGraph(width, height);
		SetDrawValidGraphCreateFlag(FALSE);
		ptr->size_w_ = width;
		ptr->size_h_ = height;
		return ptr;
	}

	Texture::SharedPtr Texture::createFromFile(const std::string& file_path) {
		return flyweight_map_.load(file_path, file_path);
	}

	std::vector<Texture::SharedPtr> Texture::createVectorFromFile(const std::string& file_path, const int all_num, const int x_num, const int y_num, const int width, const int height) {
		Texture::SharedPtr ptr = flyweight_map_.load(file_path, file_path);
		std::vector<Texture::SharedPtr> vector;
		if (!ptr) return vector;
		vector.resize(all_num);
		for (int y = 0; y < y_num; ++y) {
			for (int x = 0; x < x_num; ++x) {
				int index = x + y * x_num;
				vector[index] = ptr->partiallyCreatedFromTexture(x * width, y * height, width, height);
				if (all_num - 1 <= index) return vector;
			}
		}
		return vector;
	}

	Texture::SharedPtr Texture::fromFlyWeightLoader(const std::string& file_name, const std::string& file_path) {
		Texture::SharedPtr ptr = SharedFactory::create<Texture>();
		ptr->file_path_ = file_name;
		ptr->image_ = LoadGraph(file_path.c_str());
		GetGraphSize(ptr->image_, &ptr->size_w_, &ptr->size_h_);
		if (-1 != ptr->image_) return ptr;
		warningMassage(("テクスチャのロードに失敗 : " + file_path).c_str());
		return nullptr;
	}

	void Texture::finalize() {
		DeleteGraph(image_);
	}

}