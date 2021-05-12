#pragma once
#include "../library/t2klib.h"


namespace spe {

	class Timer final : public t2k::Singleton<Timer> {
	private:
		// ���N���X�Ő������邽��
		friend class t2k::Singleton<Timer>;

		Timer() {}

		//====================================================================================================
		// �����o�ϐ�

		// �o�ߎ���
		float time_ = TIME_LIMIT;

		//====================================================================================================
	public:
		~Timer() {}

		//====================================================================================================
		// �����o�萔

		// ��������
		inline static const float TIME_LIMIT = 180.0f;

		//====================================================================================================
		// �����o�ϐ�

		// �o�ߎ��ԁi�Q�Ɨp�j
		const float& TIME = time_;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update();

		// �N���A�^�C�����擾
		inline float getClearTime() const { return TIME_LIMIT - time_; }

		//====================================================================================================
	};

}