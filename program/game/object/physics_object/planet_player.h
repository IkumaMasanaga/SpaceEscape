#pragma once
#include "../../../engine/dxe.h"
#include "../mover/one_shot_animation.h"


namespace spe {

	enum class EndType;

	class PlanetPlayer final : public dxe::PhysicsObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetPlayer>;
		using WeakPtr = std::weak_ptr<PlanetPlayer>;
	private:
		//====================================================================================================
		// �����o�萔

		// �O�t���[���ł̕␳�����t���O
		inline static const int CORRECT_UP = 1 << 0;
		inline static const int CORRECT_DOWN = 1 << 1;
		inline static const int CORRECT_LEFT = 1 << 2;
		inline static const int CORRECT_RIGHT = 1 << 3;

		// 1�̃G�l���M�[�ŉ񕜂���l
		inline static const float ENERGY_RECOVER_VALUE = 5.0f;

		//====================================================================================================
		// �����o�ϐ�

		// �摜
		dxe::AnimationSprite::SharedPtr animation_ = nullptr;

		// �A�j���[�V�����̎���
		std::unordered_map<std::string, float> animation_time_;

		// �^�b�N�����̃g���K�[�Փ˔���
		dxe::CollisionRect::SharedPtr tackle_rect_ = nullptr;

		// �ړ���
		float move_power_ = 0.0f;

		// �ʏ펞�̈ړ���
		float default_move_power_ = 0.0f;

		// �󒆂ł̈ړ���
		float air_move_power_ = 0.0f;

		// �^�b�N�����̈ړ��͂̊���
		float tackle_move_rate_ = 1.0f;

		// �^�b�N�����t���O
		bool is_tackle_ = false;

		// �W�����v��
		float jump_power_ = 0.0f;

		// �ʏ펞�̖��C��
		t2k::Vector3 default_friction_ = t2k::Vector3::ZERO;

		// �U�����̖��C��
		t2k::Vector3 attack_friction_ = t2k::Vector3::ZERO;

		// �␳�t���O
		int correct_flag_ = 0;

		// �W�����v�\��
		bool can_jump_ = false;

		// �_���[�W���󂯂��ۂ̎��Ԍo��
		float damage_time_count_ = 0.0f;

		// �_�ŗp
		float flash_time_count_ = 0.0f;

		// �U�����󂯂���
		bool is_damage_ = false;

		// �L�[�A�C�e�����l��������
		bool is_get_key_item_ = false;

		// ���S���̃G���f�B���O�^�C�v
		EndType end_type_ = (EndType)0;

		// �^�b�N���𗭂߂Ă��鎞�̃G�t�F�N�g�̎���
		float effect_time_tackle_charge_ = 0.0f;

		// �^�b�N���𗭂߂��������̃G�t�F�N�g�̎���
		float effect_time_tackle_charge_max_ = 0.0f;

		// �^�b�N���`���[�W���G�t�F�N�g
		OneShotAnimationDesc tackle_charge_desc_;

		// �^�b�N���G�t�F�N�g
		OneShotAnimationDesc tackle_desc_;
		OneShotAnimation::WeakPtr effect_tackle_;

		// �G�l���M�[�l���G�t�F�N�g
		OneShotAnimationDesc energy_desc_;

		// ���G�t�F�N�g
		OneShotAnimationDesc smoke_desc_;
		OneShotAnimation::WeakPtr effect_smoke_;

		// �O�Ր����p�J�E���^
		float generate_locus_time_count_ = 0.0f;

		// �^�b�N������SE�Ăяo���p�J�E���^
		float tackle_se_count_ = 0.0f;

		// �O�ՃG�t�F�N�g
		OneShotAnimationDesc locus_desc_;

		// �O�Չ摜�̃t�@�C���p�X
		std::vector<std::string> locus_file_paths_;

		// �V�[�P���X�����p
		t2k::Sequence<PlanetPlayer*> seq_ = t2k::Sequence<PlanetPlayer*>(this, &PlanetPlayer::seqIdle);

		//====================================================================================================
		// �����o�֐�
		
		// ������
		void onCreated() final override;

		// �X�V
		void update() final override;

		// �Փˎ�
		void onCollisionOfPhysicsObject(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;
		
		// �ҋ@�V�[�P���X
		bool seqIdle();

		// �U���V�[�P���X
		bool seqAttack();

		// �^�b�N���`���[�W�V�[�P���X
		bool seqEnergyActionCharge();

		// �^�b�N�����s�V�[�P���X
		bool seqEnergyActionAttack();

		// �_���[�W�󂯂����V�[�P���X
		bool seqDamage();

		// ���S���V�[�P���X
		bool seqDeath();

		// �_���[�W�ɂ��_��
		void flashByDamage();

		//====================================================================================================
	public:
		PlanetPlayer() {}
		~PlanetPlayer() {}

		//====================================================================================================
		// �����o�֐�

		// �L�[�A�C�e�����l���������̐ݒ�
		inline void setGetKeyItem(const bool is_get_key_item) { is_get_key_item_ = is_get_key_item; }

		// �L�[�A�C�e�����l��������
		inline bool isGetKeyItem() const { return is_get_key_item_; }

		//====================================================================================================
	};

}
