#include "scene.h"
#include "dx_engine.h"
#include "collision_manager.h"
#include "physics.h"
#include "screen.h"
#include "object/object.h"


namespace dxe {

	void Scene::update() {

		// �I�u�W�F�N�g�̍X�V

		// �X�V�D��x�̏��������Ƀ��X�g����ёւ���
		updates_.sort([](const Object::SharedPtr left, const Object::SharedPtr right) {
			return left->update_priority_ < right->update_priority_;
		});

		std::list<Object::SharedPtr>::iterator it = updates_.begin();

		// �o�^����Ă��邷�ׂẴI�u�W�F�N�g�ɂ���
		while (it != updates_.end()) {
			// ��������
			if (!(*it)->isAlive()) {
				it = updates_.erase(it);
				continue;
			}
			// �X�V�t���O�������Ă��邩�A��ɍX�V����ꍇ
			if (is_update_game_object_ || (*it)->is_update_always_) {
				// �L������
				if ((*it)->isActive()) {
					(*it)->update();
				}
			}
			++it;
		}

		// Scene�h���N���X�̍X�V
		lateUpdate();

		// �������Z�ƏՓ˔���
		if (is_update_game_object_) {

			Physics::getInstance().update();
			CollisionManager& collision_manager = CollisionManager::getInstance();
			collision_manager.collision();
			collision_manager.updatePrevPosition();

		}

	}

	void Scene::render() {

		// �`��D��x�̏��������Ƀ��X�g����ёւ���
		screens_.sort([](const std::shared_ptr<Screen> right, const std::shared_ptr<Screen> left) {
			return right->priority_ < left->priority_;
		});

		// �X�N���[���͈͓��ɕ`��
		for (const auto& screen : screens_) {
			screen->renderToTexture();
		}

		// �X�N���[���̕`��
		for (const auto& screen : screens_) {
			screen->render();
		}

	}

	std::list<std::shared_ptr<Object>> Scene::getObjects(const std::string& name) const {
		std::list<std::shared_ptr<Object>> ret;
		// �o�^����Ă��邷�ׂẴI�u�W�F�N�g�ɂ���
		for (const auto& obj : updates_) {
			// ���O����v���Ă��Ȃ���Ύ���
			if (obj->getName() != name) continue;
			ret.emplace_back(obj);
		}
		return ret;
	}

	std::shared_ptr<Screen> Scene::getScreen(const std::string& name) const {
		// �o�^����Ă��邷�ׂẴX�N���[���ɂ���
		for (const auto& screen : screens_) {
			// �o�^������v���Ă��Ȃ���Ύ���
			if (screen->getRegisteredName() != name) continue;
			return screen;
		}
		warningMassage(("Screen��������܂���ł��� : " + name).c_str());
		return nullptr;
	}

	std::shared_ptr<Screen> Scene::createScreenToScene(const std::string& screen_name, std::shared_ptr<Camera2D> camera, const int width, const int height) {
		// �o�^����Ă��邷�ׂẴX�N���[���ɂ���
		for (const auto& screen : screens_) {
			// �o�^������v���Ă��Ȃ���Ύ���
			if (screen->getRegisteredName() != screen_name) continue;
			warningMassage(("Screen�����d�����Ă��܂� : " + screen_name).c_str());
			return nullptr;
		}
		Screen::SharedPtr ptr = Screen::create(camera, width, height);
		ptr->registered_name_ = screen_name;
		ptr->scene_ = shared_from_this();
		screens_.emplace_back(ptr);
		return ptr;
	}

}
