#pragma once
#include "../engine/dxe.h"
#include "../system/dx_main.h"


namespace spe {

	// �f���ԍ�
	enum class PlanetID {
		SUN,		// ���z
		MERCURY,	// ����
		VENUS,		// ����
		EARTH,		// �n��
		MARS,		// �ΐ�
		JUPITER,	// �ؐ�
		SATURN,		// �y��
		URANUS,		// �V����
		NEPTUNE,	// �C����
		PLUTO		// ������
	};

	// ����G���h�̎��
	enum class EndType {
		BAD_TIME_UP,			// ���z�����G���h
		BAD_SUN_EXPLOSION,		// ���z�\���G���h
		BAD_SUN_BURNING,		// ���z�ܔM�G���h
		BAD_NEPTUNE_POISON,		// �C�����ŃK�X�G���h
		BAD_PLANET_ENEMY,		// �G�ΐ����G���h
		BAD_PLANET_FALLING,		// �f�������G���h
		BAD_PLANET_JUMP_OUT,	// �F����яo���G���h
		BAD_SPACE_ENERGY,		// �F���Y���G���h
		BAD_NEW_WORLD_POISON,	// �V�f���ŃK�X�G���h
		BAD_NEW_WORLD_BURNING,	// �V�f���ܔM�G���h
		GOOD_NEW_WORLD,			// �V�f�����K�G���h
		GOOD_SURVIVAL,			// ���҃G���h
		TRUE_PLUTO,				// ���I�`�G���h�i�������j
	};

	class SaveData final : public t2k::Singleton<SaveData> {
	private:
		// ���N���X�Ő������邽��
		friend class t2k::Singleton<SaveData>;
		// initialize, finalize���ĂԂ���
		friend class sys::DxMain;

		SaveData() {}

		//====================================================================================================
		// �����o�ϐ�

		// �N���A�������Ƃ�����G���f�B���O
		int clear_ends_ = 0;

		// �l���������Ƃ�����A�C�e��
		int get_items_ = 0;

		// �V�f�����K�G���h�̃����L���O
		float good_new_world_ranking_[3] = { 0.0f };

		// ���҃G���h�̃����L���O
		float good_survival_ranking_[3] = { 0.0f };

		//====================================================================================================
		// �����o�֐�

		// ������
		void initialize();

		// �I������
		void finalize();
	
		// GOOD�G���h�̃����L���O���L�^����
		float* recordGoodRanking(const EndType end_type, const float clear_time);

		// �O���t�@�C���ɋL�^
		void save();

		// �O���t�@�C������ǂݍ���
		void load();

		//====================================================================================================
	public:
		~SaveData() {}

		//====================================================================================================
		// �����o�萔

		// �f����
		inline static const int PLANET_MAX = 10;

		// �G���f�B���O�̐�
		inline static const int ENDING_MAX = 13;

		//====================================================================================================
		// �����o�ϐ�

		// BGM�̃}�X�^�[�{�����[��
		float bgm_volume_ = 0.8f;

		// SE�̃}�X�^�[�{�����[��
		float se_volume_ = 0.8f;

		//====================================================================================================
		// �����o�֐�

		// �N���A�����G���f�B���O�̋L�^
		inline void recordClearEnd(const EndType end_type) { clear_ends_ |= (1 << (int)end_type); }

		// �G���f�B���O���N���A������
		inline bool isClearEnd(const EndType end_type) const { return clear_ends_ & (1 << (int)end_type); }

		// �l�������A�C�e�����L�^
		inline void recordGetItems(const int get_items) { get_items_ |= get_items; }

		// �A�C�e�����l��������
		inline bool hasItem(const PlanetID planet_id) const { return get_items_ & (1 << (int)planet_id); }

		// �����L���O���L�^��������I�u�W�F�N�g�𐶐�����
		dxe::Mover::SharedPtr createRankingText(const EndType end_type, const float clear_time);

		// �����L���O�̕�����I�u�W�F�N�g�𐶐�����
		dxe::Mover::SharedPtr createRankingText(const EndType end_type);

		// �O���t�@�C���ɋL�^�����f�[�^�����Z�b�g
		void reset();

		// BGM�}�X�^�[�{�����[���̕ύX
		void changeBGMVolume(const float change_value);

		// SE�}�X�^�[�{�����[���̕ύX
		void changeSEVolume(const float change_value);

		//====================================================================================================
	};

}
