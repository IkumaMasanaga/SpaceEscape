#include "mover.h"


namespace dxe {

	bool Mover::isExistence(Mover::SharedPtr transform) const {
		// �܂��͒����̎q����
		Mover::SharedPtr check = getChild(0);
		// �����̎q�����Ȃ����false
		if (!check) return false;
		// �T���������ƈ�v���Ă����true
		if (check == transform) return true;
		// �ċA�I�ɌĂяo��
		if (check->isExistence(transform)) return true;
		// ��ԉ��̎q�܂ōs�����牡�Ɍ��Ă����i��͓����j
		check = check->getNext();
		if (!check) return false;
		if (check == transform) return true;
		return check->isExistence(transform);
	}

	Mover::SharedPtr Mover::getFront() {
		// �O�����Ȃ��Ȃ�܂ōċA�I�ɌĂяo��
		if (!getPrev()) return std::dynamic_pointer_cast<Mover>(shared_from_this());
		return getPrev()->getFront();
	}

	Mover::SharedPtr Mover::getBack() {
		// ��낪���Ȃ��Ȃ�܂ōċA�I�ɌĂяo��
		if (!getNext()) return std::dynamic_pointer_cast<Mover>(shared_from_this());
		return getNext()->getBack();
	}

	Mover::SharedPtr Mover::getChild(const int count) const {
		// �q�����Ȃ��ꍇ�͏I��
		if (child_.expired()) return nullptr;
		Mover::SharedPtr ptr = child_.lock();
		// �w�肵���񐔕�
		for (int i = 0; i < count; ++i) {
			// ���̎q�����Ȃ��Ȃ������_�ŏI��
			if (!ptr) return nullptr;
			ptr = ptr->getNext();
		}
		return ptr;
	}

	int Mover::getChildCount() const {
		// �q�����Ȃ�
		if (child_.expired()) return 0;
		Mover::SharedPtr ptr = child_.lock();
		int ret = 0;
		// ���̎q�����Ȃ��Ȃ�܂�
		while (ptr) {
			ptr = ptr->getNext();
			++ret;
		}
		return ret;
	}

	void Mover::setWorldTransform(const t2k::Transform& transform) {
		// �e�����Ȃ��ꍇ�͂��̂܂ܐݒ�
		if (!getParent()) {
			transform_ = transform;
			return;
		}
		t2k::Transform wt = getWorldTransform();
		transform_.scale_ = transform.scale_ / wt.scale_;
		transform_.rotation_ = transform.rotation_ - wt.rotation_;
		transform_.position_ += toLocalPosition(transform.position_ - wt.position_);
	}

	t2k::Transform Mover::getWorldTransform() const {
		// �e�����Ȃ��ꍇ�͂��̂܂�
		if (!getParent()) return transform_;
		t2k::Transform ret;
		// �ċA�I�ɌĂяo��
		t2k::Transform pt = parent_.lock()->getWorldTransform();
		ret.position_ = pt.position_ + (t2k::Matrix::getRelativePosition(transform_.position_, pt.rotation_) * pt.scale_);
		ret.rotation_ = pt.rotation_ + transform_.rotation_;
		ret.scale_ = pt.scale_ * transform_.scale_;
		return ret;
	}

	t2k::Vector3 Mover::toLocalPosition(const t2k::Vector3& world_position) {
		if (!getParent()) return world_position;
		return t2k::Matrix::getRelativePosition(parent_.lock()->toLocalPosition(world_position), -parent_.lock()->transform_.rotation_) / parent_.lock()->transform_.scale_;
	}

	void Mover::pushChild(Mover::SharedPtr child) {
		Mover::SharedPtr m = std::dynamic_pointer_cast<Mover>(shared_from_this());
		// ���ɋt�̐e�q�֌W�����΂�Ă���ꍇ
		if (child->isExistence(m)) {
			warningMassage("�ǉ����悤�Ƃ���Transform�̎q���Ɏ��g�����݂��Ă��܂�");
			return;
		}
		// �e���痣�E������
		child->popParent();
		child->transform_.position_ = t2k::Matrix::getRelativePosition(child->transform_.position_ - transform_.position_, -transform_.rotation_) / transform_.scale_;
		child->transform_.rotation_ -= transform_.rotation_;
		child->transform_.scale_ /= transform_.scale_;
		child->parent_ = m;
		// ���Ɏq������ꍇ�͑O��֌W�����т���
		if (getChild(0)) {
			child->prev_ = child_.lock()->getBack();
			child_.lock()->getBack()->next_ = child;
		}
		else {
			child_ = child;
		}
	}

	void Mover::popParent() {
		Mover::SharedPtr parent = getParent();
		// �e�����Ȃ��ꍇ�͏I��
		if (!parent) return;
		transform_ = getWorldTransform();
		// �O��֌W�A�e�q�֌W�����т���
		if (getPrev()) {
			prev_.lock()->next_ = next_;
			if (getNext()) next_.lock()->prev_ = prev_;
		}
		else {
			parent->child_ = next_;
			if (getNext()) next_.lock()->prev_.reset();
		}
		parent_.reset();
	}

	void Mover::setActiveWithChild(const bool is_active) {
		// ���g�̗L����Ԃ�ݒ�
		setActive(is_active);
		Mover::SharedPtr child = getChild(0);
		// ���[�܂�
		while (child) {
			// �ċA�I�ɌĂяo��
			child->setActiveWithChild(is_active);
			child = child->getNext();
		}
	}

	void Mover::destroyWithChild() {
		// ���g���폜
		destroy();
		Mover::SharedPtr child = getChild(0);
		// ���[�܂�
		while (child) {
			// �ċA�I�ɌĂяo��
			child->destroyWithChild();
			child = child->getNext();
		}
	}

}
