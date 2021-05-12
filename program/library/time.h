#pragma once
#include <chrono>
#include "../system/dx_main.h"

/*====================================================================================================
* 
* ©ìŠÔŠÖŒWƒNƒ‰ƒX
* 
====================================================================================================*/

namespace t2k {

	class Time final {
	private:
		Time() {}
		Time(const Time&) = delete;
		Time& operator = (const Time&) = delete;

		friend class sys::DxMain;

		inline static std::chrono::system_clock::time_point clock_start_;
		inline static std::chrono::system_clock::time_point clock_end_;
		inline static float delta_time_ = 0.0f;
		inline static float delta_time_avg_ = 0.0f;
		inline static float elapsed_time_ = 0.0f;
		inline static int frame_count_ = 0;

		static void initialize();
		static void update();

	public:
		inline static float getDeltaTime() { return delta_time_; }
		inline static float getDeltaTimeAvg() { return delta_time_avg_; }
		inline static float getElapsedTime() { return elapsed_time_; }
		inline static int getFrameCount() { return frame_count_; }
	};

}
