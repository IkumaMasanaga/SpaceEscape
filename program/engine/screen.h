#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class Camera2D;

	// �ݒ肵�����A�����͈͓̔���Layer��`�悷��N���X
	// �͈͓���Layer�̕`��
	class Screen final : public t2k::SharedFactory<Screen> {
	public:
		using SharedPtr = std::shared_ptr<Screen>;
		using WeakPtr = std::weak_ptr<Screen>;
	private:
		// renderToTexture, render���ĂԂ��߁AScreen�����Ɠ�����scene_��ݒ肷�邽��
		friend class Scene;

		//====================================================================================================
		// �����o�ϐ�

		// ���g�̓o�^��
		std::string registered_name_;

		// ���g���������Ă���Scene
		std::weak_ptr<Scene> scene_;
		
		// Screen��`�悵�Ă���Camera2DComponent
		std::shared_ptr<Camera2D> camera_ = nullptr;

		// �`��Texture
		// ���ۂ�Layer��`�悷��ꏊ
		t2k::Texture::SharedPtr texture_ = nullptr;

		// Screen�̒��S���W
		// �E�B���h�E�̒��S�����_
		t2k::Vector3 position_ = t2k::Vector3(0, 0, 0);

		//====================================================================================================
		// �����o�֐�

		// ���g�������Ă���`��Texture��Layer��`��
		void renderToTexture();

		// ���g�������Ă���`��Texture��`��
		void render() const;

		// ���g���������Ă���Scene���擾
		inline std::shared_ptr<Scene> getScene() const { return (scene_.expired()) ? nullptr : scene_.lock(); }

		//====================================================================================================
		// static�֐�

		// Screen�̍쐬
		static Screen::SharedPtr create(std::shared_ptr<Camera2D> camera, const int width, const int height);

		//====================================================================================================
	public:
		Screen() {}
		~Screen() {}

		//====================================================================================================
		// �����o�ϐ�

		// Screen�̕`��D��x
		// �������ق�����ɕ`�悳���
		float priority_ = 0.0f;

		//====================================================================================================
		// �����o�֐�

		// Camera2D�̐؂�ւ�
		inline void changeCamera2D(std::shared_ptr<Camera2D> camera) { camera_ = camera; }

		// Camera2D�̎擾
		inline const std::shared_ptr<Camera2D> getCamera2D() const { return camera_; }
		
		// Screen�̒��S���W�̐ݒ�
		inline void setPosition(const t2k::Vector3& position) { position_ = position; }

		// Screen�̒��S���W�̎擾
		inline t2k::Vector3 getPosition() const { return position_; }

		// Screen�̕����擾
		inline int getWidth() const { return texture_->getWidth(); }
		
		// Screen�̍������擾
		inline int getHeight() const { return texture_->getHeight(); }

		// ���g�̓o�^���̎擾
		inline std::string getRegisteredName() const { return registered_name_; }

		//====================================================================================================
	};
	
}
