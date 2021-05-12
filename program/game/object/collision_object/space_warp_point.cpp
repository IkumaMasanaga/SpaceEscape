#include "space_warp_point.h"
#include "space_player.h"


namespace spe {

	void SpaceWarpPoint::update() {
		key_->setActive(false);
		planet_->transform_.rotation_ += t2k::toRadian(0.1f);
	}

	void SpaceWarpPoint::onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		// �v���C���[�ȊO�ƏՓ˂����ꍇ�͏������s��Ȃ�
		if (other->getHashCode() != dxe::Object::getHashCode<SpacePlayer>()) return;

		// �L�[��L����
		key_->setActive(true);

		is_warp_ = false;

		bool warp = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);

		if (warp) {
			is_warp_ = true;
		}

	}

	SpaceWarpPoint::SharedPtr SpaceWarpPoint::create(const std::string& csv_folder) {
		SpaceWarpPoint::SharedPtr ptr = dxe::CollisionObject::create<SpaceWarpPoint>();
		
		// �O��CSV�t�@�C������ǂݍ���
		std::vector<std::vector<std::string>> data = t2k::loadCsv(csv_folder);

		// ���[�v��CSV�t�@�C��
		ptr->warp_csv_folder_ = data[1][1];

		// �f��
		ptr->planet_ = dxe::Sprite::createFromFile(data[0][1]);
		ptr->pushChild(ptr->planet_);

		// ���[�v�G�t�F�N�g
		ptr->warp_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		ptr->pushChild(ptr->warp_);
		ptr->warp_->alpha_ = 0.75f;
		ptr->warp_->registAnimation("warp", t2k::Texture::createVectorFromFile("graphics/space/warp_space.png", 8, 8, 1, 32, 32));
		ptr->warp_->play("warp", 1.0f, true);

		// ���[�v�L�[
		ptr->key_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		ptr->pushChild(ptr->key_);
		ptr->key_->update_priority_ = -1.0f;
		ptr->key_->registAnimation("key", t2k::Texture::createVectorFromFile("graphics/ui/key_c_warp.png", 2, 2, 1, 32, 128));
		ptr->key_->play("key", 0.6f, true);

		// �Փ˔���
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(32, 32);
		rect->is_trigger_ = true;
		ptr->addCollisionRect("warp", rect);

		return ptr;
	}

}
