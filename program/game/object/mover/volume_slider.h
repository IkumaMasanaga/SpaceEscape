#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class VolumeSlider final : public dxe::Mover {
	public:
		using SharedPtr = std::shared_ptr<VolumeSlider>;
		using WeakPtr = std::weak_ptr<VolumeSlider>;
	private:
		//====================================================================================================
		// �����o�萔

		// ��
		inline static const int FRAME_WIDTH = 500;

		//====================================================================================================
		// �����o�ϐ�

		// �{�����[���ւ̃|�C���^
		float* volume_ = nullptr;

		// �܂݂̍��W�ւ̃|�C���^
		t2k::Vector3* knob_position_ = nullptr;
		t2k::Vector3* knob_frame_position_ = nullptr;

		// �{�����[���̗L����
		dxe::RectRenderer::SharedPtr active_ = nullptr;

		// �`��D��x��ύX���邽��
		std::vector<dxe::RectRenderer::SharedPtr> rects_;

		//====================================================================================================
		// �����o�֐�

		// �X�V
		void update() final override;

		//====================================================================================================
	public:
		VolumeSlider() {}
		~VolumeSlider() {}

		//====================================================================================================
		// �����o�֐�

		// �`��D��x�̕ύX
		void setRenderPriority(const float priority);

		// �L���ʂ̐F��ύX����
		inline void setActiveColor(const mylib::Color& color) { active_->color_ = color; }

		//====================================================================================================
		// static�֐�

		// ����
		static VolumeSlider::SharedPtr create(float* volume);

		//====================================================================================================
	};

}
