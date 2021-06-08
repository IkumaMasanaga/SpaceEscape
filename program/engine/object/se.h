#pragma once
#include "object.h"


namespace dxe {

	// SE�N���X
	// ���̃N���X�P�̂ł͐������܂���
	// SEManager��ʂ��Ă�������
	// ���[�v�Đ��̐ݒ�
	// �{�����[���̐ݒ�
	class SE final : public Object {
	public:
		using SharedPtr = std::shared_ptr<SE>;
		using WeakPtr = std::weak_ptr<SE>;
	private:
		// create���ĂԂ���
		friend class SEManager;

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

		// ���\�[�X�t�@�C������SE�̐���
		static SE::SharedPtr create(const std::string& file_path);

		//====================================================================================================
	public:
		SE() {}
		~SE() {}

		//====================================================================================================
		// �����o�ϐ�

		// ���[�v�Đ��t���O
		bool is_loop_ = false;

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
