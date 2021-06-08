#pragma once
#include <string>
#include "../shared_factory.h"
#include "../shared_flyweight_map.h"


namespace mylib {

	class Audio final : public t2k::SharedFactory<Audio>, public t2k::SharedFlyweightMapInterface<std::string, Audio> {
	public:
		using SharedPtr = std::shared_ptr<Audio>;
		using WeakPtr = std::weak_ptr<Audio>;
	private:
		// fromFlyWeightLoader, finalize���ĂԂ���
		friend class t2k::SharedFlyweightMapInterface<std::string, Audio>;

		//====================================================================================================
		// �����o�ϐ�
		int sound_ = 0;
		float total_time_ = 0.0f;
		std::string file_path_;

		//====================================================================================================
		// �����o�֐�
		void finalize() final override;

		//====================================================================================================
		// static�֐�
		static Audio::SharedPtr fromFlyWeightLoader(const std::string& file_name, const std::string& file_path);

	public:
		Audio() {}
		~Audio() {}

		//====================================================================================================
		// �����o�֐�
		inline int getSound() const { return sound_; }
		inline float getTotalTime() const { return total_time_; }

		//====================================================================================================
		// static�֐�
		static Audio::SharedPtr createFromFile(const std::string& file_path);
	};

}
