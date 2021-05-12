#pragma once
#include <any>
#include <memory>

namespace t2k {

	//------------------------------------------------------------------------------------------
	//
	// std::shared_ptr �ł̓��I��������������t�@�N�g���N���X
	//  
	// tips: shared_from_this �̓R���X�g���N�^�ŌĂяo���Ă͂����Ȃ��̂�
	//       ����Ƃ��� shared_from_this_constructor ���
	//       �h���N���X�ł͂����̉��z�֐��� shared_from_this ���g����R���X�g���N�^�Ƃ��Ďg�p
	//

	template< class T >
	class SharedFactory : public std::enable_shared_from_this<T> {
	private :

		// new �̎g�p���֎~
		static void* operator new(size_t i) { return _mm_malloc(i, 16); }

	protected : 
		SharedFactory() {}

		//-----------------------------------------------------------------------------------
		// �������ꂽ��ɕt�����Ď��s����鉼�z�֐� (�����Ȃ�)
		virtual void shared_from_this_constructor() {}

		//-----------------------------------------------------------------------------------
		// �������ꂽ��ɕt�����Ď��s����鉼�z�֐�
		// tips.. ������ create �Ŏw�肳�ꂽ�������n�����
		virtual void shared_from_this_constructor_exist_argument(std::any a) {}

	public :
		static void operator delete(void* p) { _mm_free(p); }
		virtual ~SharedFactory() {}

		//-----------------------------------------------------------------------------------
		// �����Ȃ��̐����֐�
		template< class U >
		static std::shared_ptr<U> create() {
			std::shared_ptr<U> ptr = std::make_shared<U>();
			ptr->shared_from_this_constructor();
			return ptr;
		}

		//-----------------------------------------------------------------------------------
		// �����t���̐����֐�
		template< class U, class Desc >
		static std::shared_ptr<U> create( Desc desc ) {
			std::shared_ptr<U> ptr = std::make_shared<U>();
			ptr->shared_from_this_constructor_exist_argument(desc);
			return ptr;
		}

	};

}