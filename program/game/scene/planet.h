#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class MessageWindow;
	class Pause;
	class PlanetPlayer;
	class PlanetKeyItem;
	class PlanetKeyItemFrame;
	class PlanetWarpPoint;

	class Planet final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Planet>;
		using WeakPtr = std::weak_ptr<Planet>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �f���ԍ�
		int id_ = -1;

		// ���b�Z�[�W�E�B���h�E
		std::shared_ptr<MessageWindow> message_window_ = nullptr;

		// �v���C���[
		std::shared_ptr<PlanetPlayer> player_ = nullptr;

		// �L�[�A�C�e��
		std::shared_ptr<PlanetKeyItem> key_item_ = nullptr;

		// �L�[�A�C�e���l�����̃t���[��
		std::shared_ptr<PlanetKeyItemFrame> key_item_frame_ = nullptr;

		// �L�[�A�C�e���l�����̂ڂ���
		dxe::Sprite::SharedPtr blur_ = nullptr;

		// HP�񕜂̃e�L�X�g
		dxe::Text::SharedPtr hp_text_ = nullptr;

		// �e�f���A�F���֍s���|�C���g
		std::list<std::shared_ptr<PlanetWarpPoint>> warp_points_;

		// ���̃V�[���ɑJ�ڂ���O�̃V�[���̏��
		std::string prev_scene_;

		// �}�b�v�A�C�x���g�A�G��񂪓����Ă���CSV�t�H���_�̃p�X
		std::string csv_folder_path_;

		// �V�[�P���X�����p
		t2k::Sequence<Planet*> seq_ = t2k::Sequence<Planet*>(this, &Planet::seqIdle);

		// �|�[�Y
		std::shared_ptr<Pause> pause_ = nullptr;

		//====================================================================================================
		// �����o�֐�

		// ������
		void initialize() final override;

		// �X�V
		void lateUpdate() final override;

		// �I������
		void finalize() final override;

		// �ʏ�
		bool seqIdle();

		// �L�[�A�C�e���l��
		bool seqGetKeyItem();

		// �|�[�Y�V�[�P���X
		bool seqPause();

		//====================================================================================================
	public:
		Planet() {}
		~Planet() {}

		//====================================================================================================
		// static�֐�

		static Planet::SharedPtr create(const std::string& prev_scene, const std::string& csv_folder_path);

		//====================================================================================================
	};

}
