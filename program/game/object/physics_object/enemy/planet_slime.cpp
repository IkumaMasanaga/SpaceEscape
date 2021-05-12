#include "planet_slime.h"
#include "../planet_energy_item.h"


namespace spe {

	void PlanetSlime::onCreatedOfEnemy() {

		// CSV�t�@�C������ǂݍ���
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/enemy/slime.csv");

		const int COLOR_MAX = 4;
		const int COLOR = rand() % COLOR_MAX;
		animation_->registAnimation("idle", t2k::Texture::createVectorFromFile(data[1+COLOR][0], std::stoi(data[1+COLOR][1]), std::stoi(data[1+COLOR][2]), std::stoi(data[1+COLOR][3]), std::stoi(data[1+COLOR][4]), std::stoi(data[1+COLOR][5])));
		animation_->registAnimation("move", t2k::Texture::createVectorFromFile(data[6+COLOR][0], std::stoi(data[6+COLOR][1]), std::stoi(data[6+COLOR][2]), std::stoi(data[6+COLOR][3]), std::stoi(data[6+COLOR][4]), std::stoi(data[6+COLOR][5])));
		animation_->play("idle", 1.0f, true);

		collision_rect_ = dxe::CollisionRect::create(std::stoi(data[11][1]), std::stoi(data[11][2]), t2k::Vector3(std::stof(data[11][3]), std::stof(data[11][4]), 0));
		collision_rect_->correct_space_.up_ = 0.0f;
		collision_rect_->is_correct_ = true;
		addCollisionRect("slime", collision_rect_);

		move_power_ = std::stof(data[12][1]);
		hp_ = std::stoi(data[13][1]);

		friction_ = t2k::Vector3(std::stof(data[14][1]), std::stof(data[14][2]), std::stof(data[14][3]));
		seq_time_max_ = std::stof(data[15][1]);
		seq_time_min_ = std::stof(data[16][1]);

		// �G�t�F�N�g
		std::vector<std::vector<std::string>> effect_data = t2k::loadCsv(data[17][1]);
		effect_desc_.file_path_ = effect_data[1][0];
		effect_desc_.all_num_ = std::stoi(effect_data[1][1]);
		effect_desc_.x_num_ = std::stoi(effect_data[1][2]);
		effect_desc_.y_num_ = std::stoi(effect_data[1][3]);
		effect_desc_.width_ = std::stoi(effect_data[1][4]);
		effect_desc_.height_ = std::stoi(effect_data[1][5]);
		effect_desc_.alive_time_ = std::stof(effect_data[2][1]);
		effect_desc_.start_alpha_ = std::stof(effect_data[3][1]);
		effect_desc_.complete_alpha_ = std::stof(effect_data[3][1]);

	}

	void PlanetSlime::update() {
		seq_.update();
		if (is_move_left_) {
			addForceTime(t2k::Vector3::LEFT * move_power_);
		}
		else if (is_move_right_) {
			addForceTime(t2k::Vector3::RIGHT * move_power_);
		}
	}

	void PlanetSlime::onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

		// �v���C���[�̒e���^�b�N���̋�`�ƏՓ˂�����
		if (rect->getName() == "bullet" || rect->getName() == "tackle") {
			dxe::SEManager::getInstance().play(dxe::SEKey::HIT);
			// �e�̏ꍇ�͏���
			if (rect->getName() == "bullet") {
				other->destroyWithChild();
			}

			--hp_;

			// ���S
			if (hp_ >= 0) {

				destroyWithChild();

				// �G�t�F�N�g�𐶐�����
				effect_desc_.start_position_ = transform_.position_;
				OneShotAnimation::create(effect_desc_);

				// �G�l���M�[������
				const int GENERATE_NUM = t2k::randomRangeI(2, 4);

				// �G�l���M�[�𐶐�
				if (rect->getName() == "bullet") {
					for (int i = 0; i < GENERATE_NUM; ++i) {
						PlanetEnergyItem::create(transform_);
					}
				}
				else {
					for (int i = 0; i < GENERATE_NUM; ++i) {
						// �^�b�N���œ|�����ꍇ�̓G�l���M�[��������ɐ�������
						PlanetEnergyItem::create(transform_)->transform_.position_ += t2k::Vector3::UP * 32;
					}
				}
			}
		}

		// �ǂɓ���������
		if (direction == dxe::CorrectDirection::LEFT) {
			if (!is_move_left_) {
				moveLeft();
			}
		}
		else if (direction == dxe::CorrectDirection::RIGHT) {
			if (is_move_left_) {
				moveRight();
			}
		}
		// ���ɂ���Ƃ�
		else if (direction == dxe::CorrectDirection::UP) {
			// �����蔻��̋�`�̍��[�����̍��[���O�ɂ�������
			if (transform_.position_.x - (collision_rect_->width_ >> 1) < rect->center_.x - (rect->width_ >> 1)) {
				if (is_move_left_) {
					moveRight();
				}
			}
			// �����蔻��̋�`�̉E�[�����̉E�[���O�ɂ�������
			else if (rect->center_.x + (rect->width_ >> 1) < transform_.position_.x + (collision_rect_->width_ >> 1)) {
				if (!is_move_left_) {
					moveLeft();
				}
			}
		}

	}

	bool PlanetSlime::seqIdle() {

		if (seq_.isStart()) {
			animation_->play("idle", 1.0f, true);
			// �V�[�P���X�؂�ւ��Ԋu�𗐐��Őݒ�
			seq_change_time_ = t2k::randomRangeF(seq_time_min_, seq_time_max_);
		}

		moveStop();

		if (seq_change_time_ < seq_.getProgressTime()) {
			seq_.change(&PlanetSlime::seqMove);
		}

		return true;
	}

	bool PlanetSlime::seqMove() {

		if (seq_.isStart()) {
			// �����ō��E�ړ����������߂�
			if (rand() % 2 == 0) {
				moveLeft();
			}
			else {
				moveRight();
			}

			animation_->play("move", 1.0f, true);
			// �V�[�P���X�؂�ւ��Ԋu�𗐐��Őݒ�
			seq_change_time_ = t2k::randomRangeF(seq_time_min_, seq_time_max_);
		}

		if (seq_change_time_ < seq_.getProgressTime()) {
			seq_.change(&PlanetSlime::seqIdle);
		}

		return true;
	}

	void PlanetSlime::moveLeft() {
		is_move_left_ = true;
		is_move_right_ = false;
		animation_->is_flip_y_ = false;
	}

	void PlanetSlime::moveRight() {
		is_move_right_ = true;
		is_move_left_ = false;
		animation_->is_flip_y_ = true;
	}

	void PlanetSlime::moveStop() {
		is_move_left_ = false;
		is_move_right_ = false;
	}

}
