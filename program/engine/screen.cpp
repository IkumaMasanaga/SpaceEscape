#include "DxLib.h"
#include "screen.h"
#include "dx_engine.h"
#include "collision_manager.h"
#include "scene.h"
#include "object/object.h"
#include "object/mover/render_object/render_object.h"


namespace dxe {

	void Screen::renderToTexture() {

		// 自身が所属しているシーン内の描画オブジェクトを描画優先度の低い順に並び替え
		getScene()->renders_.sort([](const std::shared_ptr<RenderObject> left, const std::shared_ptr<RenderObject> right) {
			return left->render_priority_ < right->render_priority_;
		});

		// 描画先を自身のテクスチャに変更
		SetDrawScreen(texture_->getImage());
		ClearDrawScreen();

		std::list<std::shared_ptr<RenderObject>>::iterator it = getScene()->renders_.begin();

		// 描画オブジェクトすべて
		while (it != getScene()->renders_.end()) {
			// 生存判定
			if (!(*it)->isAlive()) {
				it = getScene()->renders_.erase(it);
				continue;
			}
			// 有効判定
			if ((*it)->isActive()) {
				// 描画判定
				if ((*it)->isRender()) {
					(*it)->render(shared_from_this());
				}
			}
			++it;
		}

		// 衝突判定矩形の描画（デバッグ用）
		CollisionManager& collision_manager = CollisionManager::getInstance();
		if (collision_manager.is_render_debug_area_) {
			collision_manager.renderDebugArea(shared_from_this());
		}
		
		// 描画先を裏画面に戻す
		SetDrawScreen(DX_SCREEN_BACK);

	}

	void Screen::render() const {
		DxEngine& engine = DxEngine::getInstance();
		int w = engine.getWindowWidth() >> 1;	// ウィンドウの幅の半分
		int h = engine.getWindowHeight() >> 1;	// ウィンドウの高さの半分
		int rx = (int)(w + position_.x);		// 描画するワールド座標系の中心X座標
		int ry = (int)(h + position_.y);		// 描画するワールド座標系の中心Y座標

		// 描画モードのリセット
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(rx, ry, 1.0f, 0.0f, texture_->getImage(), true);
	}

	Screen::SharedPtr Screen::create(std::shared_ptr<Camera2D> camera, const int width, const int height) {
		Screen::SharedPtr ptr = SharedFactory::create<Screen>();
		ptr->camera_ = camera;
		ptr->texture_ = t2k::Texture::createRenderTexture(width, height);
		return ptr;
	}

}
