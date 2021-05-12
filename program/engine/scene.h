#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class Layer;
	class Camera2D;

	// Scene���ۃN���X
	// �Q�[������Scene�͂��̃N���X���p�����č쐬���܂�
	// Screen�̍쐬�A�o�^
	// Layer�̍쐬�A�o�^
	// �쐬����Layer��GameObject�̓o�^
	class Scene : public t2k::SharedFactory<Scene> {
	public:
		using SharedPtr = std::shared_ptr<Scene>;
		using WeakPtr = std::weak_ptr<Scene>;
	private:
		// initialize, update, render���ĂԂ���
		friend class DxEngine;
		// layers_�փA�N�Z�X���邽��
		friend class Screen;
		// Object�����Ɠ�����updates_�֓o�^���邽��
		friend class Object;
		// RenderObject�����Ɠ�����renders_�֓o�^���邽��
		friend class RenderObject;

		//====================================================================================================
		// �����o�ϐ�

		// �X�V����Object�Ǘ����X�g
		// �������ꂽObject��DxEngine��now_scene_�������Ă���updates_�Ɏ����œo�^�����
		std::list<std::shared_ptr<Object>> updates_;

		// �`�悷��RenderObject
		// �������ꂽRenderObject��DxEngine��now_scene_�������Ă���renders_�Ɏ����œo�^�����
		std::list<std::shared_ptr<RenderObject>> renders_;

		// �`�悷��Screen�Ǘ����X�g
		std::list<std::shared_ptr<Screen>> screens_;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update();

		// �`��
		void render();

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�֐�

		// �������i�������z�֐��j
		virtual void initialize() = 0;

		// Scene���Ƃ̍X�V
		// GameObject�̍X�V�I����Ɏ��s�����
		virtual void lateUpdate() {}

		// �I������
		// ���BGM�̒�~
		virtual void finalize() {}

		//====================================================================================================
	public:
		Scene() {}
		virtual ~Scene() {}

		//====================================================================================================
		// �����o�ϐ�

		// GameObject�̍X�V�t���O
		// ���̃t���O���~�낷�ƍX�V�A�������Z�A�Փ˔�����s��Ȃ��i�`��͍s���j
		bool is_update_game_object_ = true;

		//====================================================================================================
		// �����o�֐�

		// Scene���ŊǗ����Ă���GameObject�̎擾
		// updates_���疼�O�Ō������Ĉ�v������̂�list�ŕԂ�
		std::list<std::shared_ptr<Object>> getObjects(const std::string& name) const;

		// Screen�̎擾
		std::shared_ptr<Screen> getScreen(const std::string& name) const;

		// Scene����Screen�𐶐�
		std::shared_ptr<Screen> createScreenToScene(const std::string& screen_name, std::shared_ptr<Camera2D> camera, const int width, const int height);

		//====================================================================================================
		// static�֐�

		// Scene�̐���
		// �e���v���[�g�����ɂ�Scene�N���X�̔h���N���X���w�肷��
		template<class TScene>
		static std::shared_ptr<TScene> create() { return SharedFactory::create<TScene>(); }

		//====================================================================================================
	};

}
