#pragma once
#include "../../engine/dxe.h"


namespace spe {

	class Pause;
	class SpacePlayer;
	class SpaceWarpPoint;

	class Space final : public dxe::Scene {
	public:
		using SharedPtr = std::shared_ptr<Space>;
		using WeakPtr = std::weak_ptr<Space>;
	private:
		//====================================================================================================
		// �����o�萔

		// �w�i�̃J��������̕`�拗��
		inline static const float BACKGROUND_RENDER_POSITION_FROM_CAMERA = 0.25f;

		//====================================================================================================
		// �����o�ϐ�

		t2k::Sequence<Space*> seq_ = t2k::Sequence<Space*>(this, &Space::seqPlay);

		// �O�ɂ����f���̔ԍ�
		int prev_planet_id_ = -1;

		// �����o������̃��C��
		int goal_line_ = 0;

		// �w�i
		dxe::Sprite::SharedPtr bg1_ = nullptr;
		dxe::Sprite::SharedPtr bg2_ = nullptr;

		// ���E�̐Ԙg
		dxe::Sprite::SharedPtr view_red_ = nullptr;

		// ���E�̐Ԙg�̃A���t�@�l
		float red_alpha_ = 0.5f;

		// �x��SE�̍Đ��Ԋu�p�J�E���^
		float warning_time_count_ = 0.0f;
		
		// �A���t�@�l�̐���p
		t2k::TimerFluct<float> red_alpha_controller_;

		// �w�i�̕�
		int bg_width_ = 0;

		// �v���C���[
		std::shared_ptr<SpacePlayer> player_ = nullptr;

		// ���[�v�|�C���g
		std::vector<std::shared_ptr<SpaceWarpPoint>> warp_points_;

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

		// �v���C�V�[�P���X
		bool seqPlay();

		// �|�[�Y�V�[�P���X
		bool seqPause();

		//====================================================================================================
	public:
		Space() {}
		~Space() {}

		//====================================================================================================
		// static�֐�

		// ����
		static Space::SharedPtr create(const int prev_planet_id);

		//====================================================================================================
	};

}
