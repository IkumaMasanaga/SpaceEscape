#pragma once
#include <functional>
#include "mylib/time.h"

namespace t2k {

	template <class T>
	class Sequence final {
	private:
		T object_;
		std::function<bool(T)> now_;
		std::function<bool(T)> next_;
		bool is_start_ = true;
		bool is_change_ = false;
		float sum_time_ = 0;
		Sequence() {}
	public:

		//===================================================================================
		// �R���X�g���N�^
		// arg1... ��܃N���X�� this �|�C���^���w��
		// arg2... �R�[���o�b�N�ŌĂяo��������܃N���X�̃����o���\�b�h�܂��̓����_���w��
		//===================================================================================
		Sequence(const T obj, const std::function<bool(T)> func)
			: object_(obj)
			, next_(func)
			, now_(func)
		{}
		~Sequence() {}

		//===================================================================================
		// �V�[�P���X�̃A�b�v�f�[�g ( ���t���[���Ăяo����OK )
		// arg1... �t���[���Ԃ̌o�ߎ���( �b�̃f���^�^�C�� )
		//===================================================================================
		inline bool update() {
			sum_time_ += mylib::Time::getDeltaTime();
			bool ret = now_(object_);
			if (!is_change_) {
				is_start_ = false;
				return ret ;
			}
			now_ = next_;
			is_start_ = true;
			sum_time_ = 0;
			is_change_ = false;
			return ret;
		}

		//===================================================================================
		// �������p�@�V�[�P���X�̍ŏ��̂P�t���[������ true ���A��
		//===================================================================================
		inline bool isStart() const { return is_start_; }

		//===================================================================================
		// �V�[�P���X�̌o�ߎ��Ԃ��擾 ( �b )
		//===================================================================================
		inline float getProgressTime() const { return sum_time_; }

		//===================================================================================
		// �V�[�P���X�̕ύX
		// arg1... ���̃t���[��������s�������܃N���X�̃��\�b�h���w��
		//===================================================================================
		inline void change(const std::function<bool(T)> func) {
			next_ = func; 
			is_change_ = true;
		}

		//===================================================================================
		// �V�[�P���X�𑦍��ɕύX
		// arg1... ���s�������܃N���X�̃��\�b�h���w��
		// tisp... ���t���[����҂��������ɃV�[�P���X��ύX����
		//===================================================================================
		inline void immediatelyChange(const std::function<bool(T)> func) {
			now_ = func;
			is_start_ = true;
			sum_time_ = 0;
			is_change_ = false;
		}

	};

}

