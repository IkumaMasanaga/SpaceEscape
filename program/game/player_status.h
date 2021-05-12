#pragma once
#include <algorithm>
#include "../library/t2klib.h"


namespace spe {

	enum class PlanetID;

	class PlayerStatus final : public t2k::Singleton<PlayerStatus> {
	private:
		// ���N���X�Ő������邽��
		friend class t2k::Singleton<PlayerStatus>;

		PlayerStatus() {}

		//====================================================================================================
		// �����o�ϐ�

		// HP
		int hp_ = MAX_HP;

		// �G�l���M�[
		float energy_ = MAX_ENERGY * 0.5f;

		// ������G�l���M�[
		float temp_energy_ = 0.0f;

		// �����A�C�e��
		unsigned int items_ = 0;

		//====================================================================================================
	public:
		~PlayerStatus() {}

		//====================================================================================================
		// �����o�萔

		// HP
		inline static const int MAX_HP = 10;

		// �G�l���M�[
		inline static const float MAX_ENERGY = 200.0f;

		//====================================================================================================
		// �����o�֐�

		// HP
		inline int getHP() const { return hp_; }
		inline void changeHP(const int value) { hp_ = std::clamp(hp_ + value, 0, MAX_HP); }

		// �G�l���M�[
		inline float getEnergy() const { return energy_; }
		inline bool changeEnergy(const float value) {
			bool ret = false;
			if (energy_ == MAX_ENERGY) ret = true;
			energy_ = std::clamp(energy_ + value, 0.0f, MAX_ENERGY);
			return ret;
		}

		// ������G�l���M�[
		inline float getTempEnergy() const { return temp_energy_; }
		inline void changeTempEnergy(const float value) { temp_energy_ = std::clamp(temp_energy_ + value, 0.0f, energy_); }
		inline void resetTempEnergy() { temp_energy_ = 0.0f; }
		inline void reflectTempEnergy(const float reflect_value) {
			if (temp_energy_ - reflect_value < 0.0f) {
				changeEnergy(-temp_energy_);
				temp_energy_ = 0.0f;
			}
			else {
				changeEnergy(-reflect_value);
				changeTempEnergy(-reflect_value);
			}
		}

		// �����A�C�e��
		inline int getItems() const { return items_; }
		inline bool hasItem(const PlanetID id) const { return items_ & (1 << (int)id); }
		inline void getItem(const PlanetID id) { items_ |= (1 << (int)id); }

		//====================================================================================================
	};

}
