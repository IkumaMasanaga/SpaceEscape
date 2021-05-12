#pragma once


namespace t2k {

	// �e�����ɍ��v�����ꍇ�ɏ������l��-1.0f�`1.0f�̊Ԃ𑝌�����N���X
	// �ŏ��ɏ�����ݒ肵�Č��getValue�Œl���󂯎�邾��
	class SmoothNormalize final {
	private:
		//====================================================================================================
		// �����o�ϐ�

		float value_ = 0.0f;
		float ips_ = 1.0f;
		bool* positive_ = nullptr;
		bool* negative_ = nullptr;

		//====================================================================================================
	public:
		SmoothNormalize() {}
		~SmoothNormalize() {}

		//====================================================================================================
		// �����o�֐�

		// �����̃|�C���^�̐ݒ�
		void setCondition(bool* negative, bool* positive);

		// �X�V
		// ���t���[���Ă�
		void update();

		// 1�b������̑����ʂ̐ݒ�
		// IPS = Increase Per Second
		inline void setIPS(const float ips) { ips_ = ips; }

		// �l�̎擾
		inline float getValue() const { return value_; }

		// �l�̃��Z�b�g
		inline void resetValue() { value_ = 0.0f; }

		//====================================================================================================
	};

}
