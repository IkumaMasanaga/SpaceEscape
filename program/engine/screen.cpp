#include "DxLib.h"
#include "screen.h"
#include "dx_engine.h"
#include "collision_manager.h"
#include "scene.h"
#include "object/object.h"
#include "object/mover/render_object/render_object.h"


namespace dxe {

	void Screen::renderToTexture() {

		// ���g���������Ă���V�[�����̕`��I�u�W�F�N�g��`��D��x�̒Ⴂ���ɕ��ёւ�
		getScene()->renders_.sort([](const std::shared_ptr<RenderObject> left, const std::shared_ptr<RenderObject> right) {
			return left->render_priority_ < right->render_priority_;
		});

		// �`�������g�̃e�N�X�`���ɕύX
		SetDrawScreen(texture_->getImage());
		ClearDrawScreen();

		std::list<std::shared_ptr<RenderObject>>::iterator it = getScene()->renders_.begin();

		// �`��I�u�W�F�N�g���ׂ�
		while (it != getScene()->renders_.end()) {
			// ��������
			if (!(*it)->isAlive()) {
				it = getScene()->renders_.erase(it);
				continue;
			}
			// �L������
			if ((*it)->isActive()) {
				// �`�攻��
				if ((*it)->isRender()) {
					(*it)->render(shared_from_this());
				}
			}
			++it;
		}

		// �Փ˔����`�̕`��i�f�o�b�O�p�j
		CollisionManager& collision_manager = CollisionManager::getInstance();
		if (collision_manager.is_render_debug_area_) {
			collision_manager.renderDebugArea(shared_from_this());
		}
		
		// �`���𗠉�ʂɖ߂�
		SetDrawScreen(DX_SCREEN_BACK);

	}

	void Screen::render() const {
		DxEngine& engine = DxEngine::getInstance();
		int w = engine.getWindowWidth() >> 1;	// �E�B���h�E�̕��̔���
		int h = engine.getWindowHeight() >> 1;	// �E�B���h�E�̍����̔���
		int rx = (int)(w + position_.x);		// �`�悷�郏�[���h���W�n�̒��SX���W
		int ry = (int)(h + position_.y);		// �`�悷�郏�[���h���W�n�̒��SY���W

		// �`�惂�[�h�̃��Z�b�g
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
