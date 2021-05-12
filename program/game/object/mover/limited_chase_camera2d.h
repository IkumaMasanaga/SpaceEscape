#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	// �����\����
	struct LimitedChaseCamera2DDesc {
		t2k::Vector3* chase_position_ = nullptr;	// �ǂ���������W�̃|�C���^
		float lerp_value_ = 0.1f;					// ���`�⊮��������l
		t2k::Vector3 top_left_limit_;				// �͈͂̍�����W�i���[���h���W�n�j
		t2k::Vector3 bottom_right_limit_;			// �͈͂̉E�����W�i���[���h���W�n�j
	};

	class LimitedChaseCamera2D final : public dxe::Camera2D {
	public:
		using SharedPtr = std::shared_ptr<LimitedChaseCamera2D>;
		using WeakPtr = std::weak_ptr<LimitedChaseCamera2D>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// �ǂ���������W�̃|�C���^
		t2k::Vector3* chase_position_ = nullptr;

		// ���`�⊮��������l
		float lerp_value_ = 0.1f;

		// �͈͂̍�����W�i���[���h���W�n�j
		t2k::Vector3 top_left_limit_;

		// �͈͂̉E�����W�i���[���h���W�n�j
		t2k::Vector3 bottom_right_limit_;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update() final override;

		//====================================================================================================
	public:
		LimitedChaseCamera2D() {}
		~LimitedChaseCamera2D() {}

		//====================================================================================================
		// static�֐�

		// ����
		static LimitedChaseCamera2D::SharedPtr create(const LimitedChaseCamera2DDesc& desc);

		//====================================================================================================
	};

}
