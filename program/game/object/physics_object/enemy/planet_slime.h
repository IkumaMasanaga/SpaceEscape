#pragma once
#include "planet_enemy.h"


namespace spe {

	class PlanetSlime final : public PlanetEnemy {
	public:
		using SharedPtr = std::shared_ptr<PlanetSlime>;
		using WeakPtr = std::weak_ptr<PlanetSlime>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �V�[�P���X�ő厞��
		float seq_time_max_ = 0.0f;

		// �V�[�P���X�ŏ�����
		float seq_time_min_ = 0.0f;

		// �V�[�P���X�؂�ւ�����
		float seq_change_time_ = 0.0f;

		// ���ړ��t���O
		bool is_move_left_ = false;
		
		// �E�ړ��t���O
		bool is_move_right_ = false;

		// �ړ����x
		float move_power_ = 0;

		// ���g�̏Փ˔����`
		dxe::CollisionRect::SharedPtr collision_rect_ = nullptr;

		// �ҋ@�A�ړ��̃V�[�P���X����p
		t2k::Sequence<PlanetSlime*> seq_ = t2k::Sequence<PlanetSlime*>(this, &PlanetSlime::seqIdle);

		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreatedOfEnemy() final override;

		// �X�V
		void update() final override;

		// �Փˎ�
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		// �ҋ@�V�[�P���X
		bool seqIdle();

		// �ړ��V�[�P���X
		bool seqMove();

		// ���Ɉړ�
		void moveLeft();

		// �E�Ɉړ�
		void moveRight();

		// �ړ�����߂�
		void moveStop();

		//====================================================================================================
	public:
		PlanetSlime() {}
		~PlanetSlime() {}
	};

}
