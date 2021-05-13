#pragma once
#include "render_object.h"


namespace dxe {

	class MovieSprite final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<MovieSprite>;
		using WeakPtr = std::weak_ptr<MovieSprite>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// ����
		t2k::Movie::SharedPtr movie_ = nullptr;

		// �{�����[��
		float volume_ = 1.0f;

		//====================================================================================================
		// �����o�֐�

		// �`��
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		MovieSprite() {}
		~MovieSprite() {}

		//====================================================================================================
		// �����o�ϐ�

		// x������ɔ��]������t���O
		bool is_flip_x_ = false;

		// y������ɔ��]������t���O
		bool is_flip_y_ = false;

		//====================================================================================================
		// �����o�֐�

		// �{�����[���̕ύX
		void setVolume(float volume);

		// �Đ�
		void play(bool is_seek_top = true);

		// ��~
		void stop();

		// �Đ�����
		bool isPlaying();
		
		//====================================================================================================
		// static�֐�

		// ���\�[�X�t�@�C�����琶��
		static MovieSprite::SharedPtr createFromFile(const std::string& file_path);

		//====================================================================================================
	};

}
