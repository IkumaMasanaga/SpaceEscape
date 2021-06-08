#include "planet_warp_point.h"
#include "../physics_object/planet_player.h"


namespace spe {

	void PlanetWarpPoint::update() {
		// �F������f���ւ̃��[�v�|�C���g�̏ꍇ
		if (warp_csv_folder_ == "space_to_planet") return;
		key_->setActive(false);
	}

	void PlanetWarpPoint::onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		// �v���C���[�ȊO�͏������Ȃ�
		if (other->getHashCode() != dxe::Object::getHashCode<PlanetPlayer>()) return;
		
		is_warp_ = false;

		// �L�[��L����
		key_->setActive(true);

		bool warp = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_UP);

		// �W���C�p�b�h
		mylib::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			warp |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_Y);
		}

		if (warp) {
			is_warp_ = true;
		}
		
	}

	PlanetWarpPoint::SharedPtr PlanetWarpPoint::create(const std::string& warp_csv_folder) {
		
		PlanetWarpPoint::SharedPtr ptr = CollisionObject::create<PlanetWarpPoint>();
		ptr->warp_csv_folder_ = warp_csv_folder;

		// �F������f���ւ̃��[�v�|�C���g�̏ꍇ�͉����t�������Ȃ�
		if (warp_csv_folder == "space_to_planet") return ptr;

		// ���[�v�摜
		ptr->warp_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		ptr->pushChild(ptr->warp_);
		ptr->warp_->registAnimation("warp", t2k::Texture::createVectorFromFile((warp_csv_folder == "space") ? "graphics/planet/warp_space.png" : "graphics/planet/warp.png", 8, 8, 1, 32, 64));
		ptr->warp_->play("warp", 1.0f, true);

		// �L�[�摜
		ptr->key_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		ptr->pushChild(ptr->key_);
		ptr->key_->update_priority_ = -1.0f;
		ptr->key_->registAnimation("key", t2k::Texture::createVectorFromFile("graphics/ui/key_up_warp.png", 2, 2, 1, 32, 160));
		ptr->key_->play("key", 0.6f, true);

		// �Փ˔���
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(16, 32);
		rect->is_trigger_ = true;
		ptr->addCollisionRect("warp", rect);

		return ptr;
	}

}
