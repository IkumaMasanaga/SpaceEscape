#include "DxLib.h"
#include "util.h"
#include "audio.h"


namespace t2k {

	Audio::SharedPtr Audio::fromFlyWeightLoader(const std::string& file_name, const std::string& file_path) {
		Audio::SharedPtr ptr = SharedFactory::create<Audio>();
		ptr->file_path_ = file_name;
		ptr->sound_ = LoadSoundMem(file_path.c_str());
		long long millisecond = GetSoundTotalTime(ptr->sound_);
		ptr->total_time_ = static_cast<float>(millisecond / 1000.0);
		if (-1 != ptr->sound_) return ptr;
		warningMassage(("オーディオのロードに失敗 : " + file_path).c_str());
		return nullptr;
	}

	void Audio::finalize() {
		DeleteSoundMem(sound_);
	}

	Audio::SharedPtr Audio::createFromFile(const std::string& file_path) {
		return flyweight_map_.load(file_path, file_path);
	}

}
