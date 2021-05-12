#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class BGM;

	// BGM�̊Ǘ��p�L�[
	enum class BGMKey {
		TITLE,				// �^�C�g��
		CONFIG,				// �R���t�B�O
		PROLOGUE,			// �v�����[�O
		PLAY1,				// �v���C��
		PLAY2,				// �v���C���i�c�莞�ԏ��Ȃ��j
		EPILOGUE_CLEAR,		// �G�s���[�O�i�N���A�j
		EPILOGUE_GAME_OVER,	// �G�s���[�O�i�Q�[���I�[�o�[�j
	};

	// BGM�ꊇ�Ǘ��N���X
	// BGM�̓o�^
	// BGM�̍Đ�
	// BGM�̒�~
	// BGM�̃{�����[������
	class BGMManager final : public t2k::Singleton<BGMManager> {
	private:
		// ���N���X�Ő������邽��
		friend class t2k::Singleton<BGMManager>;
		// releaceAll���ĂԂ���
		friend class DxEngine;

		BGMManager();

		//====================================================================================================
		// �C���i�[�N���X

		// �o�^������
		class BGMRegistData final {
		public:
			std::string file_path_;
			float volume_ = 1.0f;
			bool is_loop_ = true;
		};

		//====================================================================================================
		// �����o�ϐ�

		// BGM�ꊇ�Ǘ��p�A�z�z��
		std::unordered_map<BGMKey, std::shared_ptr<BGM>> bgm_map_;

		// �o�^���ƃL�[�����т���A�z�z��
		std::unordered_map<BGMKey, BGMRegistData> regist_data_map_;

		// BGM�S�̂̃{�����[��
		float master_volume_ = 1.0f;

		//====================================================================================================
		// �����o�֐�

		// ���g���Ǘ����Ă���BGM���������
		void releaceAll();

		//====================================================================================================
	public:
		~BGMManager() {}

		//====================================================================================================
		// �����o�֐�

		// BGM�S�̂̃{�����[�����擾
		inline float getMasterVolume() const { return master_volume_; }

		// BGM�S�̂̃{�����[�����擾
		void setMasterVolume(const float master_volume);

		// BGM�̓o�^
		std::shared_ptr<BGM> registBGM(const BGMKey key);

		// BGM�̎擾
		std::shared_ptr<BGM> getBGM(const BGMKey key) const;

		// BGM�̍Đ�
		// �������� true ��ݒ肷��ƍ��Đ�����BGM���~�߂��ɏd�˂čĐ�����
		std::shared_ptr<BGM> play(const BGMKey key, const bool is_duplicate = false) const;
		
		// �ꎞ��~����SE�̍Đ��ĊJ
		void playBackAll();

		// �Đ�����BGM�̒�~
		void stop() const;
		
		// BGM�̒�~
		void stop(const BGMKey key) const;

		// BGM���Đ�����
		bool isPlaying(const BGMKey key) const;

		//====================================================================================================
	};

}
