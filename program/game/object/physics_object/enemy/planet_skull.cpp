#include "planet_skull.h"


namespace spe {

	void PlanetSkull::update() {

		animation_->is_flip_y_ = (move_power_ < 0) ? false : true;

		// �㉺�Ɉړ�
		if (is_move_up_down_) {
			transform_.position_.y += move_power_;
		}
		// ���E�Ɉړ�
		else {
			transform_.position_.x += move_power_;
		}

	}

	void PlanetSkull::onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		// �ǂɓ���������t�����Ɉړ�
		if (direction == dxe::CorrectDirection::UP ||
			direction == dxe::CorrectDirection::DOWN ||
			direction == dxe::CorrectDirection::LEFT ||
			direction == dxe::CorrectDirection::RIGHT) {
			move_power_ = -move_power_;
		}

		// �e�Ɠ������Ă��|����Ȃ�

		// �v���C���[�̒e���^�b�N���ƏՓ˂�����
		if (rect->getName() == "bullet" || rect->getName() == "tackle") {

			// �e������
			if (rect->getName() == "bullet") {
				other->destroyWithChild();
			}

			// �G�t�F�N�g
			if (effect_barrier_.expired()) {
				dxe::SEManager::getInstance().play(dxe::SEKey::HIT2);
				OneShotAnimation::SharedPtr barrier = OneShotAnimation::create(effect_desc_);
				animation_->pushChild(barrier);
				effect_barrier_ = barrier;
			}
		}

	}

	PlanetSkull::SharedPtr PlanetSkull::create(const bool is_move_up_down) {

		PlanetSkull::SharedPtr ptr = PlanetEnemy::create<PlanetSkull>();

		ptr->gravity_scale_ = 0.0f;
		ptr->is_move_up_down_ = is_move_up_down;

		// CSV�t�@�C������ǂݍ���
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/enemy/skull.csv");
		const int COLOR_MAX = 4;
		const int COLOR = rand() % COLOR_MAX;

		// �A�j���[�V����
		ptr->animation_->registAnimation("skull", t2k::Texture::createVectorFromFile(data[1+COLOR][0], std::stoi(data[1+COLOR][1]), std::stoi(data[1+COLOR][2]), std::stoi(data[1+COLOR][3]), std::stoi(data[1+COLOR][4]), std::stoi(data[1+COLOR][5])));
		ptr->animation_->play("skull", 1.0f, true);

		// �Փ˔����`
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(std::stoi(data[6][1]), std::stoi(data[6][2]), t2k::Vector3(std::stof(data[6][3]), std::stof(data[6][4]), 0));
		rect->is_correct_ = true;
		ptr->addCollisionRect("skull", rect);

		// �����ړ������̓����_��
		ptr->move_power_ = std::stof(data[7][1]) * (((rand() % 2) == 0) ? 1 : -1);

		// �G�t�F�N�g
		std::vector<std::vector<std::string>> effect_data = t2k::loadCsv(data[8][1]);
		ptr->effect_desc_.file_path_ = effect_data[1][0];
		ptr->effect_desc_.all_num_ = std::stoi(effect_data[1][1]);
		ptr->effect_desc_.x_num_ = std::stoi(effect_data[1][2]);
		ptr->effect_desc_.y_num_ = std::stoi(effect_data[1][3]);
		ptr->effect_desc_.width_ = std::stoi(effect_data[1][4]);
		ptr->effect_desc_.height_ = std::stoi(effect_data[1][5]);
		ptr->effect_desc_.alive_time_ = std::stof(effect_data[2][1]);
		ptr->effect_desc_.start_alpha_ = std::stof(effect_data[3][1]);
		ptr->effect_desc_.complete_alpha_ = std::stof(effect_data[3][1]);

		return ptr;

	}

}
