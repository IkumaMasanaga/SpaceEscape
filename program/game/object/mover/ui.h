#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class UI final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<UI>;
		using WeakPtr = std::weak_ptr<UI>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �G�l���M�[�o�[�̊J�nX���W
		float energy_start_x_ = 0.0f;

		// �f����
		// GOOD�G���h�ŃN���A���Ă���ꍇ�ɕω�����
		int planet_num_ = 0;

		// �o�ߎ���
		dxe::Text::SharedPtr time_ = nullptr;

		// HP�i����j�̃e�N�X�`��
		t2k::Texture::SharedPtr hp_;

		// HP�i�Ȃ��j�̃e�N�X�`��
		t2k::Texture::SharedPtr hp_none_;

		// HP
		std::vector<dxe::Sprite::SharedPtr> hp_sprites_;

		// �G�l���M�[�o�[
		dxe::RectRenderer::SharedPtr energy_bar_ = nullptr;

		// ������G�l���M�[�o�[
		dxe::RectRenderer::SharedPtr temp_energy_bar_ = nullptr;

		// �A�C�e��
		std::vector<dxe::Sprite::SharedPtr> item_sprites_;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update() final override;

		//====================================================================================================
	public:
		UI() {}
		~UI() {}

		//====================================================================================================
		// static�֐�

		// ����
		static UI::SharedPtr create(const std::string& csv_folder);

		//====================================================================================================
	};

}
