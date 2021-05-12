#include "scene.h"
#include "dx_engine.h"
#include "collision_manager.h"
#include "physics.h"
#include "screen.h"
#include "object/object.h"


namespace dxe {

	void Scene::update() {

		// オブジェクトの更新

		// 更新優先度の小さい順にリストを並び替える
		updates_.sort([](const Object::SharedPtr left, const Object::SharedPtr right) {
			return left->update_priority_ < right->update_priority_;
		});

		std::list<Object::SharedPtr>::iterator it = updates_.begin();

		// 登録されているすべてのオブジェクトについて
		while (it != updates_.end()) {
			// 生死判定
			if (!(*it)->isAlive()) {
				it = updates_.erase(it);
				continue;
			}
			// 更新フラグが立っているか、常に更新する場合
			if (is_update_game_object_ || (*it)->is_update_always_) {
				// 有効判定
				if ((*it)->isActive()) {
					(*it)->update();
				}
			}
			++it;
		}

		// Scene派生クラスの更新
		lateUpdate();

		// 物理演算と衝突判定
		if (is_update_game_object_) {

			Physics::getInstance().update();
			CollisionManager& collision_manager = CollisionManager::getInstance();
			collision_manager.collision();
			collision_manager.updatePrevPosition();

		}

	}

	void Scene::render() {

		// 描画優先度の小さい順にリストを並び替える
		screens_.sort([](const std::shared_ptr<Screen> right, const std::shared_ptr<Screen> left) {
			return right->priority_ < left->priority_;
		});

		// スクリーン範囲内に描画
		for (const auto& screen : screens_) {
			screen->renderToTexture();
		}

		// スクリーンの描画
		for (const auto& screen : screens_) {
			screen->render();
		}

	}

	std::list<std::shared_ptr<Object>> Scene::getObjects(const std::string& name) const {
		std::list<std::shared_ptr<Object>> ret;
		// 登録されているすべてのオブジェクトについて
		for (const auto& obj : updates_) {
			// 名前が一致していなければ次へ
			if (obj->getName() != name) continue;
			ret.emplace_back(obj);
		}
		return ret;
	}

	std::shared_ptr<Screen> Scene::getScreen(const std::string& name) const {
		// 登録されているすべてのスクリーンについて
		for (const auto& screen : screens_) {
			// 登録名が一致していなければ次へ
			if (screen->getRegisteredName() != name) continue;
			return screen;
		}
		warningMassage(("Screenが見つかりませんでした : " + name).c_str());
		return nullptr;
	}

	std::shared_ptr<Screen> Scene::createScreenToScene(const std::string& screen_name, std::shared_ptr<Camera2D> camera, const int width, const int height) {
		// 登録されているすべてのスクリーンについて
		for (const auto& screen : screens_) {
			// 登録名が一致していなければ次へ
			if (screen->getRegisteredName() != screen_name) continue;
			warningMassage(("Screen名が重複しています : " + screen_name).c_str());
			return nullptr;
		}
		Screen::SharedPtr ptr = Screen::create(camera, width, height);
		ptr->registered_name_ = screen_name;
		ptr->scene_ = shared_from_this();
		screens_.emplace_back(ptr);
		return ptr;
	}

}
