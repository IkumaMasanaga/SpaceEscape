#include "vector.h"
#include "intersect.h"
#include "math.h"
#include "DxLib.h"

namespace t2k {

	// 点と矩形の衝突判定
	bool isIntersectPointRect(const int point_x, const int point_y, const int rect_x, const int rect_y, const int rect_size) {
		int sx = rect_x - (rect_size >> 1);
		int sy = rect_y - (rect_size >> 1);
		int ex = sx + rect_size;
		int ey = sy + rect_size;
		if (point_x < sx) return false;
		if (point_x > ex) return false;
		if (point_y < sy) return false;
		if (point_y > ey) return false;
		return true;
	}

	// 矩形と矩形
	bool isIntersectRectPrimitive(const int a_left, const int a_right, const int a_top, const int a_bottom,
		const int b_left, const int b_right, const int b_top, const int b_bottom) {
		if (a_right < b_left) return false;
		if (a_left > b_right) return false;
		if (a_top > b_bottom) return false;
		if (a_bottom < b_top) return false;
		return true;
	}

	// 矩形と矩形
	bool isIntersectRect(const int a_rect_x, const int a_rect_y, const int a_rect_size_w, const int a_rect_size_h,
		const int b_rect_x, const int b_rect_y, const int b_rect_size_w, const int b_rect_size_h) {

		int a_right = a_rect_x + (a_rect_size_w >> 1);
		int a_left = a_rect_x - (a_rect_size_w >> 1);
		int a_top = a_rect_y - (a_rect_size_h >> 1);
		int a_bottom = a_rect_y + (a_rect_size_h >> 1);

		int b_right = b_rect_x + (b_rect_size_w >> 1);
		int b_left = b_rect_x - (b_rect_size_w >> 1);
		int b_top = b_rect_y - (b_rect_size_h >> 1);
		int b_bottom = b_rect_y + (b_rect_size_h >> 1);

		return isIntersectRectPrimitive(a_left, a_right, a_top, a_bottom, b_left, b_right, b_top, b_bottom);
	}

	// 矩形と矩形の衝突検知 & 座標補正
	int isIntersectRectToCorrectPosition(t2k::Vector3& a_now, const t2k::Vector3 &a_prev, const int a_rect_size_w, const int a_rect_size_h,
		const t2k::Vector3& b, const int b_rect_size_w, const int b_rect_size_h,
		const float correct_space_up, const float correct_space_down, const float correct_space_left, const float correct_space_right) {

		const int NO_HIT = 0;
		const int CORRECT_LEFT = 1;
		const int CORRECT_RIGHT = 2;
		const int CORRECT_UP = 3;
		const int CORRECT_DOWN = 4;

		if (!t2k::isIntersectRect(a_now, a_rect_size_w, a_rect_size_h, b, b_rect_size_w, b_rect_size_h)) return NO_HIT;

		t2k::Vector3 a_near = t2k::getNearestRectPoint(a_prev, (float)a_rect_size_w, (float)a_rect_size_h, b);
		int n = t2k::getRegionPointAndRect(a_near, b, b_rect_size_w, b_rect_size_h);

		if (0 == n) {
			float y = (a_now - a_prev).y;
			// 下向きに移動している場合は上に補正
			if (y >= 0) {
				a_now.y = b.y - (b_rect_size_h / 2) - (a_rect_size_h / 2) - correct_space_up;
				return CORRECT_UP;
			}
			// 上向きに移動している場合は左右どちらかに補正
			else {
				// 右に補正
				if (a_now.x > b.x) {
					a_now.x = b.x + (b_rect_size_w / 2) + (a_rect_size_w / 2) + correct_space_right;
					return CORRECT_RIGHT;
				}
				// 左に補正
				else {
					a_now.x = b.x - (b_rect_size_w / 2) - (a_rect_size_w / 2) - correct_space_left;
					return CORRECT_LEFT;
				}
			}
		}
		else if (2 == n) {
			float y = (a_now - a_prev).y;
			// 上向きに移動している場合は下に補正
			if (y <= 0) {
				a_now.y = b.y + (b_rect_size_h / 2) + (a_rect_size_h / 2) + correct_space_down;
				return CORRECT_DOWN;
			}
			// 上向きに移動している場合は左右どちらかに補正
			else {
				// 右に補正
				if (a_now.x > b.x) {
					a_now.x = b.x + (b_rect_size_w / 2) + (a_rect_size_w / 2) + correct_space_right;
					return CORRECT_RIGHT;
				}
				// 左に補正
				else {
					a_now.x = b.x - (b_rect_size_w / 2) - (a_rect_size_w / 2) - correct_space_left;
					return CORRECT_LEFT;
				}
			}
		}
		else if (1 == n) {
			float x = (a_now - a_prev).x;
			// 左向きに移動している場合は右に補正
			if (x <= 0) {
				a_now.x = b.x + (b_rect_size_w / 2) + (a_rect_size_w / 2) + correct_space_right;
				return CORRECT_RIGHT;
			}
			// 右向きに移動している場合は上下どちらかに補正
			else {
				// 上に補正
				if (a_now.y < b.y) {
					a_now.y = b.y - (b_rect_size_h / 2) - (a_rect_size_h / 2) - correct_space_up;
					return CORRECT_UP;
				}
				// 下に補正
				else {
					a_now.y = b.y + (b_rect_size_h / 2) + (a_rect_size_h / 2) + correct_space_down;
					return CORRECT_DOWN;
				}
			}
		}
		else if (3 == n) {
			float x = (a_now - a_prev).x;
			// 右向きに移動している場合は左に補正
			if (x >= 0) {
				a_now.x = b.x - (b_rect_size_w / 2) - (a_rect_size_w / 2) - correct_space_right;
				return CORRECT_LEFT;
			}
			// 左向きに移動している場合は上下どちらかに補正
			else {
				// 上に補正
				if (a_now.y < b.y) {
					a_now.y = b.y - (b_rect_size_h / 2) - (a_rect_size_h / 2) - correct_space_up;
					return CORRECT_UP;
				}
				// 下に補正
				else {
					a_now.y = b.y + (b_rect_size_h / 2) + (a_rect_size_h / 2) + correct_space_down;
					return CORRECT_DOWN;
				}
			}
		}
		return NO_HIT;
	}

	// 矩形と矩形の衝突検知 & 座標補正(オフセット値指定)
	int isIntersectRectToCorrectPositionOffset(t2k::Vector3& a_now, const t2k::Vector3& a_offset, const t2k::Vector3& a_prev, const int a_rect_size_w, const int a_rect_size_h,
		const t2k::Vector3& b, const t2k::Vector3& b_offset, const int b_rect_size_w, const int b_rect_size_h,
		const float correct_space_up, const float correct_space_down, const float correct_space_left, const float correct_space_right) {

		t2k::Vector3 a_rect_pos = a_now + a_offset;
		t2k::Vector3 a_rect_prev_pos = a_prev + a_offset;
		t2k::Vector3 b_rect_pos = b + b_offset;
		int correct = t2k::isIntersectRectToCorrectPosition(a_rect_pos, a_rect_prev_pos, a_rect_size_w, a_rect_size_h,
															b_rect_pos, b_rect_size_w, b_rect_size_h,
															correct_space_up, correct_space_down, correct_space_left, correct_space_right);
		a_now = a_rect_pos - a_offset;
		return correct;
	}

	// 円と円
	bool isIntersectCircle(const t2k::Vector3& a, float a_radius, const t2k::Vector3& b, float b_radius) {
		float l = (a - b).length();
		return l < (a_radius + b_radius) ? true : false;
	}


}