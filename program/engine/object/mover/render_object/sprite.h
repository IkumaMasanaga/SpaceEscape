#pragma once
#include "render_object.h"


namespace dxe {

	class Sprite final : public RenderObject {
	public:
		using SharedPtr = std::shared_ptr<Sprite>;
		using WeakPtr = std::weak_ptr<Sprite>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �`��e�N�X�`��
		t2k::Texture::SharedPtr texture_;

		//====================================================================================================
		// �����o�֐�

		// �`��
		void render(std::shared_ptr<Screen> screen) final override;

		//====================================================================================================
	public:
		Sprite() {}
		~Sprite() {}

		//====================================================================================================
		// �����o�ϐ�

		// x������ɔ��]������t���O
		bool is_flip_x_ = false;

		// y������ɔ��]������t���O
		bool is_flip_y_ = false;

		//====================================================================================================
		// �����o�֐�

		// �e�N�X�`���̎擾�i�Q�Ɨp�j
		inline const t2k::Texture::SharedPtr getTexture() { return texture_; }

		// �e�N�X�`���̕ύX
		inline void changeTexture(const t2k::Texture::SharedPtr texture) { texture_ = texture; }

		//====================================================================================================
		// static�֐�

		// �e�N�X�`�����琶��
		static Sprite::SharedPtr createFromTexture(t2k::Texture::SharedPtr texture);

		// ���\�[�X�t�@�C�����琶��
		static Sprite::SharedPtr createFromFile(const std::string& file_path);

		//====================================================================================================
	};

}
