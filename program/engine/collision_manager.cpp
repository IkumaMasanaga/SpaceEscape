#include "DxLib.h"
#include "collision_manager.h"
#include "screen.h"
#include "object/mover/collision_object.h"
#include "object/collision_rect.h"
#include "object/mover/camera2d.h"


namespace dxe {

	void CollisionManager::updatePrevPosition() {
		// 登録されているすべてのオブジェクトについて
		for (const auto& cobj : collision_objects_) {
			cobj->prev_position_ = cobj->getWorldTransform().position_;
		}
	}

	void CollisionManager::collision() {

		// どちらかのis_trigger_フラグが立っている場合は補正しない
		// is_correct_フラグがXORの場合は補正しない
		// 親子でも衝突判定は行う

		// 4分木実装したい

		// 更新優先度の小さい順にリストを並び替える
		collision_objects_.sort([](const Object::SharedPtr left, const Object::SharedPtr right) {
			return left->update_priority_ < right->update_priority_;
		});

		// Aは先頭から
		std::list<std::shared_ptr<CollisionObject>>::iterator a_it = collision_objects_.begin();
		while (a_it != collision_objects_.end()) {
			// A生死判定
			if (!(*a_it)->isAlive()) {
				a_it = collision_objects_.erase(a_it);
				continue;
			}
			// A有効判定
			if (!(*a_it)->isActive()) {
				++a_it;
				continue;
			}

			// BはAの次から
			std::list<std::shared_ptr<CollisionObject>>::iterator b_it = a_it;
			++b_it;
			while (b_it != collision_objects_.end()) {
				// B生死判定
				if (!(*b_it)->isAlive()) {
					b_it = collision_objects_.erase(b_it);
					continue;
				}
				// B有効判定
				if (!(*b_it)->isActive()) {
					++b_it;
					continue;
				}

				std::list<std::shared_ptr<CollisionRect>>::iterator a_rect_it = (*a_it)->collision_area_.begin();
				while (a_rect_it != (*a_it)->collision_area_.end()) {
					// Aの衝突判定矩形1つの生死判定
					if (!(*a_rect_it)->isAlive()) {
						a_rect_it = (*a_it)->collision_area_.erase(a_rect_it);
						continue;
					}
					// Aの衝突判定矩形1つの有効判定
					if (!(*a_rect_it)->isActive()) {
						++a_rect_it;
						continue;
					}

					std::list<std::shared_ptr<CollisionRect>>::iterator b_rect_it = (*b_it)->collision_area_.begin();
					while (b_rect_it != (*b_it)->collision_area_.end()) {
						// Bの衝突判定矩形1つの生死判定
						if (!(*b_rect_it)->isAlive()) {
							b_rect_it = (*b_it)->collision_area_.erase(b_rect_it);
							continue;
						}
						// Bの衝突判定矩形1つの有効判定
						if (!(*b_rect_it)->isActive()) {
							++b_rect_it;
							continue;
						}

						//--------------------------------------------------
						// 衝突判定処理開始

						t2k::Transform a_t = (*a_it)->getWorldTransform();		// Aのワールド座標
						t2k::Vector3 a_offset = t2k::Matrix::getRelativePosition((*a_rect_it)->center_, a_t.rotation_) * a_t.scale_;	// Aの衝突判定矩形1つのオフセット値
						int a_w = (int)((*a_rect_it)->width_ * a_t.scale_);		// Aの衝突判定矩形1つの幅
						int a_h = (int)((*a_rect_it)->height_ * a_t.scale_);	// Aの衝突判定矩形1つの高さ

						t2k::Transform b_t = (*b_it)->getWorldTransform();		// Bのワールド座標
						t2k::Vector3 b_offset = t2k::Matrix::getRelativePosition((*b_rect_it)->center_, b_t.rotation_) * b_t.scale_;	// Bの衝突判定矩形1つのオフセット値
						int b_w = (int)((*b_rect_it)->width_ * b_t.scale_);		// Bの衝突判定矩形1つの幅
						int b_h = (int)((*b_rect_it)->height_ * b_t.scale_);	// Bの衝突判定矩形1つの高さ

						// どちらかのCollisionRectがトリガー指定か補正フラグがXORの場合は補正しない
						if ((*a_rect_it)->is_trigger_ || (*b_rect_it)->is_trigger_ || !((*a_rect_it)->is_correct_ ^ (*b_rect_it)->is_correct_)) {
							// 衝突している場合
							if (t2k::isIntersectRect(a_t.position_ + a_offset, a_w, a_h, b_t.position_ + b_offset, b_w, b_h)) {
								(*a_it)->onCollision((*b_it), (*b_rect_it), CorrectDirection::NONE);
								(*b_it)->onCollision((*a_it), (*a_rect_it), CorrectDirection::NONE);
							}
						}
						else {
							// Aが補正対象
							if ((*a_rect_it)->is_correct_) {
								t2k::Vector3 a_prev_pos = (*a_it)->prev_position_;
								t2k::Vector3 a_correct_pos = a_t.position_;
								int correct = t2k::isIntersectRectToCorrectPositionOffset(a_correct_pos, a_offset, a_prev_pos, a_w, a_h, b_t.position_, b_offset, b_w, b_h,
																						  (*a_rect_it)->correct_space_.up_, (*a_rect_it)->correct_space_.down_,
																						  (*a_rect_it)->correct_space_.left_, (*a_rect_it)->correct_space_.right_);
								switch (correct) {
								case 0: ++b_rect_it; continue;
								case 1:	(*a_it)->onCollision((*b_it), (*b_rect_it), CorrectDirection::LEFT);	break;
								case 2:	(*a_it)->onCollision((*b_it), (*b_rect_it), CorrectDirection::RIGHT);	break;
								case 3:	(*a_it)->onCollision((*b_it), (*b_rect_it), CorrectDirection::UP);		break;
								case 4:	(*a_it)->onCollision((*b_it), (*b_rect_it), CorrectDirection::DOWN);	break;
								}
								(*b_it)->onCollision((*a_it), (*a_rect_it), CorrectDirection::NONE);
								(*a_it)->transform_.position_ += (*a_it)->toLocalPosition(a_correct_pos - a_t.position_);
							}
							// Bが補正対象
							else {
								t2k::Vector3 b_prev_pos = (*b_it)->prev_position_;
								t2k::Vector3 b_correct_pos = b_t.position_;
								int correct = t2k::isIntersectRectToCorrectPositionOffset(b_correct_pos, b_offset, b_prev_pos, b_w, b_h, a_t.position_, a_offset, a_w, a_h,
																						  (*b_rect_it)->correct_space_.up_, (*b_rect_it)->correct_space_.down_,
																						  (*b_rect_it)->correct_space_.left_, (*b_rect_it)->correct_space_.right_);
								switch (correct) {
								case 0: ++b_rect_it; continue;
								case 1:	(*b_it)->onCollision((*a_it), (*a_rect_it), CorrectDirection::LEFT);	break;
								case 2:	(*b_it)->onCollision((*a_it), (*a_rect_it), CorrectDirection::RIGHT);	break;
								case 3:	(*b_it)->onCollision((*a_it), (*a_rect_it), CorrectDirection::UP);		break;
								case 4:	(*b_it)->onCollision((*a_it), (*a_rect_it), CorrectDirection::DOWN);	break;
								}
								(*a_it)->onCollision((*b_it), (*b_rect_it), CorrectDirection::NONE);
								(*b_it)->transform_.position_ += (*b_it)->toLocalPosition(b_correct_pos - b_t.position_);
							}
						}

						//--------------------------------------------------
						++b_rect_it;
					}
					++a_rect_it;
				}
				++b_it;
			}
			++a_it;
		}

	}

	void CollisionManager::renderDebugArea(std::shared_ptr<Screen> screen) const {
		// 登録されているすべてのオブジェクトについて
		for (const auto& cobj : collision_objects_) {

			t2k::Transform ot = cobj->getWorldTransform();					// オブジェクトのワールド座標
			t2k::Transform ct = screen->getCamera2D()->getWorldTransform();	// カメラのワールド座標
			float crs = screen->getCamera2D()->render_scale_;				// カメラの描画スケール
			float scl = ot.scale_ * crs;									// オブジェクトの描画スケール

			// オブジェクトに登録されているすべての衝突判定矩形について
			for (const auto& rect : cobj->collision_area_) {

				// 有効ではない場合は描画しない
				if (!rect->isActive()) continue;
				
				t2k::Vector3 p = ot.position_ + (t2k::Matrix::getRelativePosition(rect->center_, ot.rotation_) * ot.scale_);	// ワールド座標系の矩形の中心座標
				int sw = screen->getWidth() >> 1;	// スクリーンの幅の半分
				int sh = screen->getHeight() >> 1;	// スクリーンの高さの半分
				int l = sw + (int)(((p.x - ct.position_.x) * crs) - ((rect->width_ >> 1) * scl));	// ワールド座標系の矩形の左端
				int t = sh + (int)(((p.y - ct.position_.y) * crs) - ((rect->height_ >> 1) * scl));	// ワールド座標系の矩形の上端
				int r = sw + (int)(((p.x - ct.position_.x) * crs) + ((rect->width_ >> 1) * scl));	// ワールド座標系の矩形の右端
				int b = sh + (int)(((p.y - ct.position_.y) * crs) + ((rect->height_ >> 1) * scl));	// ワールド座標系の矩形の下端

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
				DrawFillBox(l, t, r, b, 0xFF00FF00);
				DrawLineBox(l, t, r, b, 0xFFFFFFFF);
			}
		}
	}

}
