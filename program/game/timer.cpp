#include "timer.h"
#include "player_status.h"
#include "save_data.h"


namespace spe {

	void Timer::update() {

		// 制限時間が経過していれば処理しない
		if (time_ <= 0.0f) return;

		PlayerStatus& status = PlayerStatus::getInstance();
		
		// 減少させる値
		float decrease_time = mylib::Time::getDeltaTime();

		// プレイヤーのアイテムの所持状況によって割合を変える
		if (status.hasItem(PlanetID::MERCURY)) decrease_time *= 0.5f;
		if (status.hasItem(PlanetID::SATURN)) decrease_time *= 0.5f;

		// 減らす
		time_ = std::clamp(time_ - decrease_time, 0.0f, TIME_LIMIT);
	}

}
