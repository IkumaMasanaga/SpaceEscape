#pragma once
#include "../object.h"


namespace dxe {

	class Mover : public Object {
	public:
		using SharedPtr = std::shared_ptr<Mover>;
		using WeakPtr = std::weak_ptr<Mover>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// ���g�̐e
		Mover::WeakPtr parent_;

		// ���g���q�Ƃ����Ƃ��̑O
		Mover::WeakPtr prev_;

		// ���g���q�Ƃ����Ƃ��̎�
		Mover::WeakPtr next_;

		// ���g��e�Ƃ����Ƃ��̎q�̐擪
		Mover::WeakPtr child_;

		//====================================================================================================
		// �����o�֐�

		// �w�肵��Transform�����g�����[�g�Ƃ��đ��݂��邩
		bool isExistence(Mover::SharedPtr transform) const;

		// ���g���q�Ƃ��Đ擪�̎q�̎擾
		Mover::SharedPtr getFront();

		// ���g���q�Ƃ��čŌ�̎q�̎擾
		Mover::SharedPtr getBack();

		// ���g���q�Ƃ��đO�̎q�̎擾
		inline Mover::SharedPtr getPrev() const { return (prev_.expired()) ? nullptr : prev_.lock(); }

		// ���g���q�Ƃ��Ď��̎q�̎擾
		inline Mover::SharedPtr getNext() const { return (next_.expired()) ? nullptr : next_.lock(); }

		//====================================================================================================
	protected:

	public:
		Mover() {}
		virtual ~Mover() {}

		//====================================================================================================
		// �����o�ϐ�

		// ���W�A��]�A�g�嗦
		t2k::Transform transform_;

		//====================================================================================================
		// �����o�֐�

		// �e�̎擾
		inline Mover::SharedPtr getParent() const { return (parent_.expired()) ? nullptr : parent_.lock(); }

		// �q�̎擾
		// �擪���琔�������l���w��
		Mover::SharedPtr getChild(const int count) const;

		// ���g�̒����̎q�̐����擾
		int getChildCount() const;

		// �ŏI�I��Transform�̐ݒ�
		void setWorldTransform(const t2k::Transform& transform);

		// �ŏI�I�ȃ��[���h���W�̎擾
		t2k::Transform getWorldTransform() const;

		// ���[���h���W���烍�[�J�����W�ɕϊ�
		t2k::Vector3 toLocalPosition(const t2k::Vector3& world_position);

		// �q���Ō���ɒǉ�
		void pushChild(Mover::SharedPtr child);

		// ���g���e���痣�E
		void popParent();

		// ���g�Ǝq���̗L����Ԃ�ύX
		void setActiveWithChild(const bool is_active);

		// ���g�Ǝq�������ׂď���
		void destroyWithChild();

		//====================================================================================================
	};

}
