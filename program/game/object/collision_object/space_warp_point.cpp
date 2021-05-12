#include "space_warp_point.h"
#include "space_player.h"


namespace spe {

	void SpaceWarpPoint::update() {
		key_->setActive(false);
		planet_->transform_.rotation_ += t2k::toRadian(0.1f);
	}

	void SpaceWarpPoint::onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		// プレイヤー以外と衝突した場合は処理を行わない
		if (other->getHashCode() != dxe::Object::getHashCode<SpacePlayer>()) return;

		// キーを有効に
		key_->setActive(true);

		is_warp_ = false;

		bool warp = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);

		if (warp) {
			is_warp_ = true;
		}

	}

	SpaceWarpPoint::SharedPtr SpaceWarpPoint::create(const std::string& csv_folder) {
		SpaceWarpPoint::SharedPtr ptr = dxe::CollisionObject::create<SpaceWarpPoint>();
		
		// 外部CSVファイルから読み込み
		std::vector<std::vector<std::string>> data = t2k::loadCsv(csv_folder);

		// ワープ先CSVファイル
		ptr->warp_csv_folder_ = data[1][1];

		// 惑星
		ptr->planet_ = dxe::Sprite::createFromFile(data[0][1]);
		ptr->pushChild(ptr->planet_);

		// ワープエフェクト
		ptr->warp_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		ptr->pushChild(ptr->warp_);
		ptr->warp_->alpha_ = 0.75f;
		ptr->warp_->registAnimation("warp", t2k::Texture::createVectorFromFile("graphics/space/warp_space.png", 8, 8, 1, 32, 32));
		ptr->warp_->play("warp", 1.0f, true);

		// ワープキー
		ptr->key_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		ptr->pushChild(ptr->key_);
		ptr->key_->update_priority_ = -1.0f;
		ptr->key_->registAnimation("key", t2k::Texture::createVectorFromFile("graphics/ui/key_c_warp.png", 2, 2, 1, 32, 128));
		ptr->key_->play("key", 0.6f, true);

		// 衝突判定
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(32, 32);
		rect->is_trigger_ = true;
		ptr->addCollisionRect("warp", rect);

		return ptr;
	}

}
