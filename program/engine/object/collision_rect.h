#pragma once
#include "object.h"


namespace dxe {

	// ���W�␳���̌���
	class CorrectSpace final {
	public:
		CorrectSpace() {}
		CorrectSpace(const float up, const float down, const float left, const float right) : up_(up), down_(down), left_(left), right_(right) {}
		~CorrectSpace() {}
		
		//====================================================================================================
		// �����o�ϐ�

		// ���g��������ɕ␳���ꂽ�Ƃ��̌���
		float up_ = 1.0f;

		// ���g���������ɕ␳���ꂽ�Ƃ��̌���
		float down_ = 1.0f;

		// ���g���������ɕ␳���ꂽ�Ƃ��̌���
		float left_ = 1.0f;

		// ���g���E�����ɕ␳���ꂽ�Ƃ��̌���
		float right_ = 1.0f;

		//====================================================================================================
	};
	
	// �Փ˔����`1�̃N���X
	class CollisionRect final : public Object {
	public:
		using SharedPtr = std::shared_ptr<CollisionRect>;
		using WeakPtr = std::weak_ptr<CollisionRect>;
	public:
		CollisionRect() {}
		~CollisionRect() {}

		//====================================================================================================
		// �����o�ϐ�

		// transform_����̑��΍��W
		t2k::Vector3 center_ = t2k::Vector3::ZERO;

		// ��
		int width_ = 32;

		// ����
		int height_ = 32;

		// �g���K�[�t���O
		bool is_trigger_ = false;

		// �␳�t���O
		bool is_correct_ = false;

		// �␳���̊Ԋu
		CorrectSpace correct_space_;

		//====================================================================================================
		// static�֐�

		// ����
		static CollisionRect::SharedPtr create(const int width, const int height, const t2k::Vector3& center = t2k::Vector3());

		//====================================================================================================
	};

}
