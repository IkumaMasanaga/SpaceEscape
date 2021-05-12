#include "planet_wizard.h"
#include "../planet_energy_item.h"
#include "../../collision_object/planet_enemy_bullet.h"


namespace spe {

	void PlanetWizard::onCreatedOfEnemy() {
		
		gravity_scale_ = 0.0f;

		// CSV�t�@�C������ǂݍ���
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/scene/planet/enemy/wizard.csv");
		const int COLOR_MAX = 4;
		const int COLOR = rand() % COLOR_MAX;

		animation_->registAnimation("idle", t2k::Texture::createVectorFromFile(data[1+COLOR][0], std::stoi(data[1+COLOR][1]), std::stoi(data[1+COLOR][2]), std::stoi(data[1+COLOR][3]), std::stoi(data[1+COLOR][4]), std::stoi(data[1+COLOR][5])));
		animation_->registAnimation("attack", t2k::Texture::createVectorFromFile(data[6+COLOR][0], std::stoi(data[6+COLOR][1]), std::stoi(data[6+COLOR][2]), std::stoi(data[6+COLOR][3]), std::stoi(data[6+COLOR][4]), std::stoi(data[6+COLOR][5])));
		animation_->play("idle", 1.0f, true);

		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create(std::stoi(data[11][1]), std::stoi(data[11][2]), t2k::Vector3(std::stof(data[11][3]), std::stof(data[11][4]), 0));
		rect->is_trigger_ = true;
		addCollisionRect("wizard", rect);

		hp_ = std::stoi(data[12][1]);

		shot_time_ = std::stof(data[13][1]);
		shot_speed_ = std::stof(data[14][1]);

		// �G�t�F�N�g
		std::vector<std::vector<std::string>> effect_data = t2k::loadCsv(data[15][1]);
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

	void PlanetWizard::update() {
		seq_.update();
		sin_y_.isCompleteUpdate();
	}

	void PlanetWizard::onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) {

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
						PlanetEnergyItem::create(transform_)->transform_.position_ += t2k::Vector3::UP * 16;
					}
				}
			}
		}

	}

	bool PlanetWizard::seqInit() {

		sin_y_.setMethodSin(&transform_.position_.y, transform_.position_.y + 5, 1.0f);

		seq_.change(&PlanetWizard::seqIdle);

		return true;
	}

	bool PlanetWizard::seqIdle() {

		if (seq_.isStart()) {
			animation_->play("idle", 1.0f, true);
		}

		// �e���ˊԊu�𒴂�����V�[�P���X�؂�ւ�
		if (shot_time_ < seq_.getProgressTime()) {
			seq_.change(&PlanetWizard::seqAttack);
		}

		return true;
	}

	bool PlanetWizard::seqAttack() {

		if (seq_.isStart()) {
			animation_->play("attack", 0.4f, false);
			// 4�����ɒe���΂�
			PlanetEnemyBullet::create(t2k::Vector3::UP, shot_speed_, transform_);
			PlanetEnemyBullet::create(t2k::Vector3::DOWN, shot_speed_, transform_);
			PlanetEnemyBullet::create(t2k::Vector3::LEFT, shot_speed_, transform_);
			PlanetEnemyBullet::create(t2k::Vector3::RIGHT, shot_speed_, transform_);
		}

		// �A�j���[�V�������I��������V�[�P���X�؂�ւ�
		if (!animation_->isPlaying()) {
			seq_.change(&PlanetWizard::seqIdle);
		}

		return true;
	}

}
