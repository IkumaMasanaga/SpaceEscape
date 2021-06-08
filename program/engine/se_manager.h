#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class SE;

	// SE�̊Ǘ��p�L�[
	enum class SEKey {
		ENTER,				// ����
		SELECT,				// �I��
		BACK,				// �߂�
		JUMP,				// �W�����v
		ATTACK,				// �U��
		DAMAGE,				// �_���[�W���󂯂���
		WARP,				// ���[�v
		ITEM,				// �A�C�e���l��
		HIT,				// �U������������
		ENERGY,				// �G�l���M�[�l��
		PAUSE,				// �|�[�Y
		JET,				// �W�F�b�g
		LIMIT,				// �c�莞��30
		HIT2,				// �U�����e���ꂽ
		TACKLE,				// �^�b�N�����s
		SMOKE,				// ��
		PREPARE_TACKLE_1,	// �^�b�N�����ߒ�
		PREPARE_TACKLE_2,	// �^�b�N�����ߊ���
		WARNING,			// �G�l���M�[�c��킸��
	};

	// SE�ꊇ�Ǘ��N���X
	// SE�̓o�^
	// SE�̍Đ�
	// SE�̒�~
	// SE�̃{�����[������
	class SEManager final : public mylib::Singleton<SEManager> {
	private:
		// ���N���X�Ő������邽��
		friend class mylib::Singleton<SEManager>;
		// releaceAll���ĂԂ���
		friend class DxEngine;

		SEManager();

		//====================================================================================================
		// �C���i�[�N���X

		// �o�^������
		class SERegistData final {
		public:
			std::string file_path_;
			float volume_ = 1.0f;
			bool is_loop_ = false;
		};

		//====================================================================================================
		// �����o�ϐ�

		// SE�ꊇ�Ǘ��p�A�z�z��
		std::unordered_map<SEKey, std::shared_ptr<SE>> se_map_;

		// �o�^���ƃL�[�����т���A�z�z��
		std::unordered_map<SEKey, SERegistData> regist_data_map_;

		// SE�S�̂̃{�����[��
		float master_volume_ = 1.0f;

		//====================================================================================================
		// �����o�֐�

		// ���g���Ǘ����Ă���SE���������
		void releaceAll();

		//====================================================================================================
	public:
		~SEManager() {}

		//====================================================================================================
		// �����o�֐�

		// SE�S�̂̃{�����[�����擾
		inline float getMasterVolume() const { return master_volume_; }
		
		// SE�S�̂̃{�����[����ݒ�
		void setMasterVolume(const float master_volume);

		// SE�̓o�^
		std::shared_ptr<SE> registSE(const SEKey key);

		// SE�̎擾
		std::shared_ptr<SE> getSE(const SEKey key) const;
		
		// SE�̍Đ�
		std::shared_ptr<SE> play(const SEKey key) const;

		// �ꎞ��~����SE�̍Đ��ĊJ
		void playBackAll();

		// �Đ�����SE�̒�~
		void stop() const;

		// SE�̒�~
		void stop(const SEKey key) const;

		// SE���Đ�����
		bool isPlaying(const SEKey key) const;

		//====================================================================================================
	};

}
