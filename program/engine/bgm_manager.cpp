#include <algorithm>
#include "DxLib.h"
#include "bgm_manager.h"
#include "object/bgm.h"


namespace dxe {

	BGMManager::BGMManager() {
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/sound/bgm.csv");
		for (int i = 0; i < (int)data.size(); ++i) {
			BGMRegistData regist_data;
			regist_data.file_path_ = data[i][0];
			regist_data.volume_ = std::stof(data[i][1]);
			regist_data.is_loop_ = data[i][2] == "TRUE";
			regist_data_map_.try_emplace((BGMKey)i, regist_data);
		}
	}

	void BGMManager::setMasterVolume(const float master_volume) {
		// ”ÍˆÍ‚Ì§ŒÀ
		master_volume_ = std::clamp(master_volume, 0.0f, 1.0f);
		// Œ»İ“o˜^‚³‚ê‚Ä‚¢‚éBGM‚Ìƒ{ƒŠƒ…[ƒ€‚ğ•ÏX
		for (const auto& bgm : bgm_map_) {
			ChangeVolumeSoundMem((int)(master_volume_ * (bgm.second->getVolume() * 255)), bgm.second->getAudio()->getSound());
		}
	}

	std::shared_ptr<BGM> BGMManager::registBGM(const BGMKey key) {
		// Šù‚É“o˜^‚³‚ê‚Ä‚¢‚éê‡
		if (bgm_map_.find(key) != bgm_map_.end()) {
			warningMassage(("BGMKey‚ªd•¡‚µ‚Ä‚¢‚Ü‚· Key : " + std::to_string((int)key)).c_str());
			return nullptr;
		}
		std::shared_ptr<BGM> ptr = BGM::create(regist_data_map_[key].file_path_);
		bgm_map_.try_emplace(key, ptr);
		ptr->setVolume(regist_data_map_[key].volume_);
		ptr->is_loop_ = regist_data_map_[key].is_loop_;
		return ptr;
	}

	std::shared_ptr<BGM> BGMManager::getBGM(const BGMKey key) const {
		std::unordered_map<BGMKey, std::shared_ptr<BGM>>::const_iterator it = bgm_map_.find(key);
		// “o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡
		if (it == bgm_map_.end()) {
			warningMassage(("BGM‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ Key : " + std::to_string((int)key)).c_str());
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<BGM> BGMManager::play(const BGMKey key, const bool is_duplicate) const {
		// d‚Ë‚ÄÄ¶‚³‚¹‚È‚¢ê‡
		if (!is_duplicate) stop();
		std::unordered_map<BGMKey, std::shared_ptr<BGM>>::const_iterator it = bgm_map_.find(key);
		// “o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡
		if (it == bgm_map_.end()) {
			warningMassage(("BGM‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ Key : " + std::to_string((int)key)).c_str());
			return nullptr;
		}
		ChangeVolumeSoundMem((int)(master_volume_ * (it->second->getVolume() * 255)), it->second->getAudio()->getSound());
		if (it->second->is_loop_) {
			PlaySoundMem(it->second->getAudio()->getSound(), DX_PLAYTYPE_LOOP);
		}
		else {
			PlaySoundMem(it->second->getAudio()->getSound(), DX_PLAYTYPE_BACK);
		}
		return it->second;
	}

	void BGMManager::playBackAll() {
		// “o˜^‚³‚ê‚Ä‚¢‚é‚·‚×‚Ä‚ÌBGM‚É‚Â‚¢‚Ä
		for (const auto& bgm : bgm_map_) {
			if (!bgm.second->is_pause_) continue;
			bgm.second->is_pause_ = false;
			if (bgm.second->is_loop_) {
				PlaySoundMem(bgm.second->getAudio()->getSound(), DX_PLAYTYPE_LOOP, false);
			}
			else {
				PlaySoundMem(bgm.second->getAudio()->getSound(), DX_PLAYTYPE_BACK, false);
			}
		}
	}

	void BGMManager::stop() const {
		// “o˜^‚³‚ê‚Ä‚¢‚é‚·‚×‚Ä‚ÌBGM‚É‚Â‚¢‚Ä
		for (const auto& bgm : bgm_map_) {
			if (!CheckSoundMem(bgm.second->getAudio()->getSound())) continue;
			bgm.second->is_pause_ = true;
			StopSoundMem(bgm.second->getAudio()->getSound());
		}
	}

	void BGMManager::stop(const BGMKey key) const {
		std::unordered_map<BGMKey, std::shared_ptr<BGM>>::const_iterator it = bgm_map_.find(key);
		// “o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡
		if (it == bgm_map_.end()) {
			warningMassage(("BGM‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ Key : " + std::to_string((int)key)).c_str());
			return;
		}
		if (!CheckSoundMem(it->second->getAudio()->getSound())) return;
		it->second->is_pause_ = true;
		StopSoundMem(it->second->getAudio()->getSound());
	}

	bool BGMManager::isPlaying(const BGMKey key) const {
		std::unordered_map<BGMKey, std::shared_ptr<BGM>>::const_iterator it = bgm_map_.find(key);
		// “o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡
		if (it == bgm_map_.end()) {
			warningMassage(("BGM‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ‚Å‚µ‚½ Key : " + std::to_string((int)key)).c_str());
			return false;
		}
		return CheckSoundMem(it->second->getAudio()->getSound());
	}

	void BGMManager::releaceAll() {
		bgm_map_.clear();
	}

}
