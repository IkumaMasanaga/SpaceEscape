#include "../../../screen.h"
#include "../camera2d.h"
#include "rect_renderer.h"


namespace dxe {

	void RectRenderer::render(std::shared_ptr<Screen> screen) {
		setBlendMode();

		t2k::Transform t = getWorldTransform();							// 自身のワールド座標
		t2k::Transform ct = screen->getCamera2D()->getWorldTransform();	// 2Dカメラのワールド座標
		float crs = screen->getCamera2D()->render_scale_;	// カメラの描画スケール
		int sw = screen->getWidth() >> 1;					// 描画スクリーンの幅の半分
		int sh = screen->getHeight() >> 1;					// 描画スクリーンの高さの半分
		float rx = sw + (t.position_.x - ct.position_.x * render_position_from_camera_) * crs;		// 描画するワールド座標系の中心X座標
		float ry = sh + (t.position_.y - ct.position_.y * render_position_from_camera_) * crs;		// 描画するワールド座標系の中心Y座標
		float scl = t.scale_ * crs;			// 描画するスケール
		float rw = (float)(width_ >> 1);	// 描画する矩形の幅の半分
		float rh = (float)(height_ >> 1);	// 描画する矩形の高さの半分
		t2k::Vector3 p1 = t2k::Vector3(rx, ry, 0) + (t2k::Matrix::getRelativePosition(t2k::Vector3(-rw, -rh, 0), t.rotation_) * scl);	// 頂点1
		t2k::Vector3 p2 = t2k::Vector3(rx, ry, 0) + (t2k::Matrix::getRelativePosition(t2k::Vector3((width_ % 2) ? rw + 1.0f : rw, -rh, 0), t.rotation_) * scl);	// 頂点2
		t2k::Vector3 p3 = t2k::Vector3(rx, ry, 0) + (t2k::Matrix::getRelativePosition(t2k::Vector3((width_ % 2) ? rw + 1.0f : rw, (height_ % 2) ? rh + 1.0f : rh, 0), t.rotation_) * scl);		// 頂点3
		t2k::Vector3 p4 = t2k::Vector3(rx, ry, 0) + (t2k::Matrix::getRelativePosition(t2k::Vector3(-rw, (height_ % 2) ? rh + 1.0f : rh, 0), t.rotation_) * scl);	// 頂点4

		// スクリーン範囲外ならば描画しない
		if (!t2k::isIntersectRect(t2k::Vector3(rx, ry, 0), (int)(width_ * scl), (int)(height_ * scl), screen->getPosition() + t2k::Vector3((float)sw, (float)sh, 0), sw << 1, sh << 1)) return;

		DrawQuadrangle((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, (int)p3.x, (int)p3.y, (int)p4.x, (int)p4.y, color_.toInt(), is_fill_);
	}

	RectRenderer::SharedPtr RectRenderer::create(const int width, const int height, const mylib::Color& color, const bool is_fill) {
		RectRenderer::SharedPtr ptr = RenderObject::create<RectRenderer>();
		ptr->width_ = width;
		ptr->height_ = height;
		ptr->color_ = color;
		ptr->is_fill_ = is_fill;
		return ptr;
	}

}
