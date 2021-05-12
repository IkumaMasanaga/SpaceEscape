#include "time.h"


namespace t2k {

	void Time::initialize() {
		clock_start_ = std::chrono::system_clock::now();
	}

	void Time::update() {
		// �t���[���Ԃ̌o�ߎ���
		// �}�C�N���b�Ōv�����ĕb�ɕϊ�
		clock_end_ = std::chrono::system_clock::now();
		double microseconds = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(clock_end_ - clock_start_).count());
		delta_time_ = static_cast<float>(microseconds / 1000.0 / 1000.0);
		clock_start_ = clock_end_;
		elapsed_time_ += delta_time_;
		++frame_count_;
		delta_time_avg_ = elapsed_time_ / frame_count_;
	}

}
