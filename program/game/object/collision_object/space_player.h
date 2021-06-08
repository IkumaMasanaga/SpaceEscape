#pragma once
#include "../../../engine/dxe.h"
#include "../mover/one_shot_animation.h"


namespace spe {

	class SpacePlayer final : public dxe::CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<SpacePlayer>;
		using WeakPtr = std::weak_ptr<SpacePlayer>;
	private:
		//====================================================================================================
		// �����o�萔

		// �e�N�X�`���֌W
		static const int TEXTURE_INDEX_NORMAL = 0;
		static const int TEXTURE_INDEX_DOWN = 1;
		static const int TEXTURE_INDEX_UP = 2;
		static const int TEXTURE_NUM = 3;

		//====================================================================================================
		// �����o�ϐ�

		// �e�N�X�`��
		t2k::Texture::SharedPtr textures_[TEXTURE_NUM];

		// �摜
		dxe::Sprite::SharedPtr sprite_;

		// ���͗p
		bool up_ = false;
		bool down_ = false;
		bool left_ = false;
		bool right_ = false;

		// �W�F�b�g�̐����p�J�E���^
		float generate_jet_time_count_ = 0.0f;

		// �W�F�b�g�̐�������
		float generate_jet_time_ = 0.07f;

		// �W�F�b�g�̐����\����
		OneShotAnimationDesc jet_desc_;

		// �ō����x
		float speed_max_ = 0.0f;

		// �X�s�[�h�ɑ΂������G�l���M�[�̊���
		float consume_energy_rate_ = 0.0f;

		// �������ۂ������p�iX���j
		mylib::SmoothNormalize x_;

		// �������ۂ������p�iY���j
		mylib::SmoothNormalize y_;

		// ���S�t���O
		bool is_dead_ = false;

		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreated() final override;

		// �X�V
		void update() final override;

		// �Փˎ�
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		SpacePlayer() {}
		~SpacePlayer() {}

		//====================================================================================================
		// �����o�֐�

		// ���S�t���O�̎擾
		inline bool isDead() const { return is_dead_; }

		//====================================================================================================
	};

}
