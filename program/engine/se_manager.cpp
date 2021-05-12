#include <algorithm>
#include "DxLib.h"
#include "se_manager.h"
#include "object/se.h"


namespace dxe {

	SEManager::SEManager() {
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/sound/se.csv");
		for (int i = 0; i < (int)data.size(); ++i) {
			SERegistData regist_data;
			regist_data.file_path_ = data[i][0];
			regist_data.volume_ = std::stof(data[i][1]);
			regist_data.is_loop_ = data[i][2] == "TRUE";
			regist_data_map_.try_emplace((SEKey)i, regist_data);
		}
	}

	void SEManager::setMasterVolume(const float master_volume) {
		// �͈͂̐���
		master_volume_ = std::clamp(master_volume, 0.0f, 1.0f);
		// ���ݓo�^����Ă���SE�̃{�����[����ύX
		for (const auto& se : se_map_) {
			ChangeVolumeSoundMem((int)(master_volume_ * (se.second->getVolume() * 255)), se.second->getAudio()->getSound());
		}
	}

	std::shared_ptr<SE> SEManager::registSE(const SEKey key) {
		// ���ɓo�^����Ă���ꍇ
		if (se_map_.find(key) != se_map_.end()) {
			warningMassage(("SE�����d�����Ă��܂� Key : " + std::to_string((int)key)).c_str());
			return nullptr;
		}
		std::shared_ptr<SE> ptr = SE::create(regist_data_map_[key].file_path_);
		se_map_.try_emplace(key, ptr);
		ptr->setVolume(regist_data_map_[key].volume_);
		ptr->is_loop_ = regist_data_map_[key].is_loop_;
		return ptr;
	}

	std::shared_ptr<SE> SEManager::getSE(const SEKey key) const {
		std::unordered_map<SEKey, std::shared_ptr<SE>>::const_iterator it = se_map_.find(key);
		// �o�^����Ă��Ȃ��ꍇ
		if (it == se_map_.end()) {
			warningMassage(("SE��������܂���ł��� Key : " + std::to_string((int)key)).c_str());
			return nullptr;
		}
		return it->second;
	}

	std::shared_ptr<SE> SEManager::play(const SEKey key) const {
		std::unordered_map<SEKey, std::shared_ptr<SE>>::const_iterator it = se_map_.find(key);
		// �o�^����Ă��Ȃ��ꍇ
		if (it == se_map_.end()) {
			warningMassage(("SE��������܂���ł��� Key : " + std::to_string((int)key)).c_str());
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

	void SEManager::playBackAll() {
		// �o�^����Ă��邷�ׂĂ�SE�ɂ���
		for (const auto& se : se_map_) {
			if (!se.second->is_pause_) continue;
			se.second->is_pause_ = false;
			if (se.second->is_loop_) {
				PlaySoundMem(se.second->getAudio()->getSound(), DX_PLAYTYPE_LOOP, false);
			}
			else {
				PlaySoundMem(se.second->getAudio()->getSound(), DX_PLAYTYPE_BACK, false);
			}
		}
	}

	void SEManager::stop() const {
		// �o�^����Ă��邷�ׂĂ�SE�ɂ���
		for (const auto& se : se_map_) {
			if (!CheckSoundMem(se.second->getAudio()->getSound())) continue;
			se.second->is_pause_ = true;
			StopSoundMem(se.second->getAudio()->getSound());
		}
	}

	void SEManager::stop(const SEKey key) const {
		std::unordered_map<SEKey, std::shared_ptr<SE>>::const_iterator it = se_map_.find(key);
		// �o�^����Ă��Ȃ��ꍇ
		if (it == se_map_.end()) {
			warningMassage(("SE��������܂���ł��� Key : " + std::to_string((int)key)).c_str());
			return;
		}
		if (!CheckSoundMem(it->second->getAudio()->getSound())) return;
		it->second->is_pause_ = true;
		StopSoundMem(it->second->getAudio()->getSound());
	}

	bool SEManager::isPlaying(const SEKey key) const {
		std::unordered_map<SEKey, std::shared_ptr<SE>>::const_iterator it = se_map_.find(key);
		// �o�^����Ă��Ȃ��ꍇ
		if (it == se_map_.end()) {
			warningMassage(("SE��������܂���ł��� Key : " + std::to_string((int)key)).c_str());
			return false;
		}
		return CheckSoundMem(it->second->getAudio()->getSound());
	}

	void SEManager::releaceAll() {
		se_map_.clear();
	}

}
