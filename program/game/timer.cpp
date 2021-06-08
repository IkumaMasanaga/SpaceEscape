#include "timer.h"
#include "player_status.h"
#include "save_data.h"


namespace spe {

	void Timer::update() {

		// �������Ԃ��o�߂��Ă���Ώ������Ȃ�
		if (time_ <= 0.0f) return;

		PlayerStatus& status = PlayerStatus::getInstance();
		
		// ����������l
		float decrease_time = mylib::Time::getDeltaTime();

		// �v���C���[�̃A�C�e���̏����󋵂ɂ���Ċ�����ς���
		if (status.hasItem(PlanetID::MERCURY)) decrease_time *= 0.5f;
		if (status.hasItem(PlanetID::SATURN)) decrease_time *= 0.5f;

		// ���炷
		time_ = std::clamp(time_ - decrease_time, 0.0f, TIME_LIMIT);
	}

}
