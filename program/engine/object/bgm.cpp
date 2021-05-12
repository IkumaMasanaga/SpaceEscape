#include <algorithm>
#include "DxLib.h"
#include "../bgm_manager.h"
#include "bgm.h"


namespace dxe {

	void BGM::setVolume(const float volume) {
		// ”ÍˆÍ‚Ì§ŒÀ
		volume_ = std::clamp(volume, 0.0f, 1.0f);
		ChangeVolumeSoundMem((int)(BGMManager::getInstance().getMasterVolume() * (volume_ * 255)), audio_->getSound());
	}

	BGM::SharedPtr BGM::create(const std::string& file_path) {
		BGM::SharedPtr ptr = Object::create<BGM>();
		ptr->audio_ = t2k::Audio::createFromFile(file_path);
		return ptr;
	}

}
