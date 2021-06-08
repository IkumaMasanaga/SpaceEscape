/*
* ====================================================================================================
* 
* �V���O���g���N���X�̃e���v���[�g
* 
* ���̃N���X���p�����A�p����̃N���X�����e���v���[�g�����Ɏw��
* Singleton<�p����̃N���X��> �� friend �Ɏw��
* �R���X�g���N�^�� private �ɁA�f�X�g���N�^�� public �Ɏw��
* 
* ====================================================================================================
*/

#pragma once
#include <memory>


namespace mylib {

	template<class T>
	class Singleton {
	private:

		//====================================================================================================
		// �R�s�[�A����̋֎~
		Singleton(const Singleton&) = delete;
		Singleton& operator = (const Singleton&) = delete;

		//====================================================================================================
		// �B��̃C���X�^���X
		static T* instance_;

	protected:

		//====================================================================================================
		// �h����Ő����ł���悤�ɕی�w��
		Singleton() {}
		virtual ~Singleton() {}

	public:

		//====================================================================================================
		// �V���O���g���ȃC���X�^���X�̎擾
		inline static T& getInstance() {
			if (!instance_) {
				instance_ = new T();
			}
			return *instance_;
		}

		//====================================================================================================
		// �V���O���g���ȃC���X�^���X�̖����I�폜
		inline static void destroy() {
			if (!instance_) return;
			delete instance_;
			instance_ = nullptr;
		}

	};

	template<class T> T* Singleton<T>::instance_ = nullptr;

}
