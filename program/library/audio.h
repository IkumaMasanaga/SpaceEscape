#pragma once
#include <string>
#include "shared_factory.h"
#include "shared_flyweight_map.h"


namespace t2k {

	class Audio final : public SharedFactory<Audio>, public SharedFlyweightMapInterface<std::string, Audio> {
	public:
		using SharedPtr = std::shared_ptr<Audio>;
		using WeakPtr = std::weak_ptr<Audio>;
	private:
		// fromFlyWeightLoader, finalize‚ğŒÄ‚Ô‚½‚ß
		friend class SharedFlyweightMapInterface<std::string, Audio>;

		//====================================================================================================
		// ƒƒ“ƒo•Ï”
		int sound_ = 0;
		float total_time_ = 0.0f;
		std::string file_path_;

		//====================================================================================================
		// ƒƒ“ƒoŠÖ”
		void finalize() final override;

		//====================================================================================================
		// staticŠÖ”
		static Audio::SharedPtr fromFlyWeightLoader(const std::string& file_name, const std::string& file_path);

	public:
		Audio() {}
		~Audio() {}

		//====================================================================================================
		// ƒƒ“ƒoŠÖ”
		inline int getSound() const { return sound_; }
		inline float getTotalTime() const { return total_time_; }

		//====================================================================================================
		// staticŠÖ”
		static Audio::SharedPtr createFromFile(const std::string& file_path);
	};

}
