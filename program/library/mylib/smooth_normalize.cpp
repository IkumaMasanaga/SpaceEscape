#include <algorithm>
#include "smooth_normalize.h"
#include "time.h"


namespace mylib {

	void SmoothNormalize::setCondition(bool* negative, bool* positive) {
		negative_ = negative;
		positive_ = positive;
	}

	void SmoothNormalize::update() {
		float ipf = ips_ * Time::getDeltaTime();
		if (!(*negative_ ^ *positive_)) {
			if (value_ == 0.0f) return;
			if (value_ < 0.0f) {
				value_ = (0.0f < value_ + ipf) ? 0.0f : value_ + ipf;
			}
			else {
				value_ = (value_ + ipf < 0.0f) ? 0.0f : value_ - ipf;
			}
		}
		else {
			value_ = std::clamp(value_ + ((*negative_) ? -ipf : ipf), -1.0f, 1.0f);
		}
	}

}
