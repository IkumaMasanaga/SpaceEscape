#pragma once
#include "../mover.h"


namespace dxe {

	// �u�����h���[�h
	enum class BlendMode {
		ALPHA,	// �A���t�@�u�����h
		ADD,	// ���Z�u�����h
		SUB,	// ���Z�u�����h
		MUL		// ��Z�u�����h
	};

	// �`�悷��Object
	class RenderObject : public Mover {
	public:
		using SharedPtr = std::shared_ptr<RenderObject>;
		using WeakPtr = std::weak_ptr<RenderObject>;
	private:
		// render���ĂԂ���
		friend class Screen;
		// shared_from_this_constructor���ĂԂ���
		friend class t2k::SharedFactory<Object>;

		//====================================================================================================
		// �����o�ϐ�

		// �`��t���O
		// �`��͂��Ȃ����ǍX�V�͂������ۂɎg�p����
		bool is_render_ = true;

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�֐�

		// shared_from_this���g����R���X�g���N�^
		virtual void shared_from_this_constructor() override;

		// �`��
		virtual void render(std::shared_ptr<Screen> screen) = 0;

		//====================================================================================================
	public:
		RenderObject() {}
		virtual ~RenderObject() {}

		//====================================================================================================
		// �����o�ϐ�

		// �`��D��x
		// �������ق�����ɕ`�悳���
		float render_priority_ = 0.0f;

		// �A���t�@�l
		float alpha_ = 1.0f;

		// �u�����h���[�h
		BlendMode blend_mode_ = BlendMode::ALPHA;

		// �`�悷��Ƃ��̃J��������̋����̊���
		// ���̒l��ύX���ĕς��͕̂`��̈ʒu�����ł��i�Փ˔����`�̈ʒu�͕ς��Ȃ��j
		float render_position_from_camera_ = 1.0f;

		//====================================================================================================
		// �����o�֐�

		// �u�����h���[�h�̐ݒ�
		// �`��O�ɌĂ�
		void setBlendMode() const;

		// �`��t���O�̐ݒ�
		inline void setRender(const bool is_render) { is_render_ = is_render; }

		// �`��t���O�̎擾
		inline bool isRender() const { return is_render_; }

		//====================================================================================================
	};

}
