#pragma once
#include "object.h"


namespace dxe {

	// BGM�N���X
	// ���̃N���X�P�̂ł͐������܂���
	// BGMManager��ʂ��Ă�������
	// ���[�v�Đ��̐ݒ�
	// �{�����[���̐ݒ�
	class BGM final : public Object {
	public:
		using SharedPtr = std::shared_ptr<BGM>;
		using WeakPtr = std::weak_ptr<BGM>;
	private:
		// create���ĂԂ���
		friend class BGMManager;

		//====================================================================================================
		// �����o�ϐ�

		// Audio�n���h��
		mylib::Audio::SharedPtr audio_ = nullptr;

		// �{�����[��
		float volume_ = 1.0f;

		// �ꎞ��~����
		bool is_pause_ = false;

		//====================================================================================================
		// static�֐�

		// ���\�[�X�t�@�C������BGM�̐���
		static BGM::SharedPtr create(const std::string& file_path);

		//====================================================================================================
	public:
		BGM() {}
		~BGM() {}

		//====================================================================================================
		// �����o�ϐ�

		// ���[�v�Đ��t���O
		bool is_loop_ = true;

		//====================================================================================================
		// �����o�֐�

		// Audio�̎擾�i�Q�Ɨp�j
		inline const mylib::Audio::SharedPtr getAudio() const { return audio_; }

		// �{�����[���̎擾
		inline float getVolume() const { return volume_; }

		// �{�����[���̐ݒ�
		void setVolume(const float volume);

		//====================================================================================================
	};

}
