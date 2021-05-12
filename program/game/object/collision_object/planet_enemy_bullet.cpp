#include "planet_enemy_bullet.h"
#include "../render_object/planet_map.h"


namespace spe {

	void PlanetEnemyBullet::update() {
		// �����ɑ��x���i�߂�
		transform_.position_ += (direction_ * speed_);

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		const int WINDOW_TOP = -(engine.getWindowWidth() >> 1);
		const int WINDOW_BOTTOM = (engine.getWindowWidth() >> 1);

		// �E�B���h�E�̏㉺�ɍs���������
		if (transform_.position_.y < WINDOW_TOP ||
			WINDOW_BOTTOM < transform_.position_.y) {
			destroyWithChild();
		}

	}

	void PlanetEnemyBullet::onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		// �}�b�v���^�b�N���Ɠ��������������
		if (rect->getName() != "map" || rect->getName() != "tackle") return;
		destroyWithChild();

	}

	PlanetEnemyBullet::SharedPtr PlanetEnemyBullet::create(const t2k::Vector3& direction, const float speed, const t2k::Transform& transform) {

		PlanetEnemyBullet::SharedPtr ptr = CollisionObject::create<PlanetEnemyBullet>();

		ptr->setName("enemy");

		// ���x�̐ݒ�
		ptr->speed_ = speed;

		// �O��CSV�t�@�C������ǂݍ���
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/enemy/enemy_bullet.csv");

		// �����̐ݒ�Ɛ��K��
		ptr->direction_ = direction;
		ptr->direction_.normalize();

		// �A�j���[�V�����摜
		dxe::AnimationSprite::SharedPtr anim = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		anim->registAnimation("bullet", t2k::Texture::createVectorFromFile(data[0][1], std::stoi(data[0][2]), std::stoi(data[0][3]), std::stoi(data[0][4]), std::stoi(data[0][5]), std::stoi(data[0][6])));
		anim->play("bullet", std::stof(data[3][1]), true);
		ptr->pushChild(anim);

		// �Փ˔����`
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(std::stoi(data[1][1]), std::stoi(data[1][2]), t2k::Vector3(std::stof(data[2][1]), std::stof(data[2][2]), std::stof(data[2][3])));
		rect->is_trigger_ = true;
		ptr->addCollisionRect("enemy_bullet", rect);
		ptr->transform_ = transform;

		return ptr;
	}

}
