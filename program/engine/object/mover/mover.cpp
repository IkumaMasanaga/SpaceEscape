#include "mover.h"


namespace dxe {

	bool Mover::isExistence(Mover::SharedPtr transform) const {
		// まずは直下の子から
		Mover::SharedPtr check = getChild(0);
		// 直下の子がいなければfalse
		if (!check) return false;
		// 探したい物と一致していればtrue
		if (check == transform) return true;
		// 再帰的に呼び出す
		if (check->isExistence(transform)) return true;
		// 一番下の子まで行ったら横に見ていく（後は同じ）
		check = check->getNext();
		if (!check) return false;
		if (check == transform) return true;
		return check->isExistence(transform);
	}

	Mover::SharedPtr Mover::getFront() {
		// 前がいなくなるまで再帰的に呼び出す
		if (!getPrev()) return std::dynamic_pointer_cast<Mover>(shared_from_this());
		return getPrev()->getFront();
	}

	Mover::SharedPtr Mover::getBack() {
		// 後ろがいなくなるまで再帰的に呼び出す
		if (!getNext()) return std::dynamic_pointer_cast<Mover>(shared_from_this());
		return getNext()->getBack();
	}

	Mover::SharedPtr Mover::getChild(const int count) const {
		// 子がいない場合は終了
		if (child_.expired()) return nullptr;
		Mover::SharedPtr ptr = child_.lock();
		// 指定した回数分
		for (int i = 0; i < count; ++i) {
			// 次の子がいなくなった時点で終了
			if (!ptr) return nullptr;
			ptr = ptr->getNext();
		}
		return ptr;
	}

	int Mover::getChildCount() const {
		// 子がいない
		if (child_.expired()) return 0;
		Mover::SharedPtr ptr = child_.lock();
		int ret = 0;
		// 次の子がいなくなるまで
		while (ptr) {
			ptr = ptr->getNext();
			++ret;
		}
		return ret;
	}

	void Mover::setWorldTransform(const t2k::Transform& transform) {
		// 親がいない場合はそのまま設定
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
		// 親がいない場合はそのまま
		if (!getParent()) return transform_;
		t2k::Transform ret;
		// 再帰的に呼び出す
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
		// 既に逆の親子関係が結ばれている場合
		if (child->isExistence(m)) {
			warningMassage("追加しようとしたTransformの子供に自身が存在しています");
			return;
		}
		// 親から離脱させる
		child->popParent();
		child->transform_.position_ = t2k::Matrix::getRelativePosition(child->transform_.position_ - transform_.position_, -transform_.rotation_) / transform_.scale_;
		child->transform_.rotation_ -= transform_.rotation_;
		child->transform_.scale_ /= transform_.scale_;
		child->parent_ = m;
		// 既に子がいる場合は前後関係を結びつける
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
		// 親がいない場合は終了
		if (!parent) return;
		transform_ = getWorldTransform();
		// 前後関係、親子関係を結びつける
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
		// 自身の有効状態を設定
		setActive(is_active);
		Mover::SharedPtr child = getChild(0);
		// 末端まで
		while (child) {
			// 再帰的に呼び出す
			child->setActiveWithChild(is_active);
			child = child->getNext();
		}
	}

	void Mover::destroyWithChild() {
		// 自身を削除
		destroy();
		Mover::SharedPtr child = getChild(0);
		// 末端まで
		while (child) {
			// 再帰的に呼び出す
			child->destroyWithChild();
			child = child->getNext();
		}
	}

}
