#pragma once
#include "../library/t2klib.h"
#include "../system/dx_main.h"


namespace dxe {

	class Scene;

	class DxEngine final : public t2k::Singleton<DxEngine> {
	private:
		// ���N���X�Ő������邽��
		friend class t2k::Singleton<DxEngine>;
		// initialize, update, finalize���ĂԂ���
		friend class sys::DxMain;

		DxEngine() {}

		//====================================================================================================
		// �����o�ϐ�

		// �Q�[�����[�v�t���O
		bool is_playing_game_ = true;

		// �E�B���h�E�̕�
		int window_width_ = 0;

		// �E�B���h�E�̍���
		int window_height_ = 0;

		// ���݂̃V�[��
		std::shared_ptr<Scene> now_scene_ = nullptr;

		// ���̃V�[��
		std::shared_ptr<Scene> next_scene_ = nullptr;

		// Screen�J�ڑO��̃t�F�[�h�pSequence
		t2k::Sequence<DxEngine*> transition_sequence_ = t2k::Sequence<DxEngine*>(this, &DxEngine::seqFadeIn);

		// Screen�J�ڂ̃A���t�@�l�p
		t2k::TimerFluct<float> transition_controller_;

		// Screen�J�ڂ̃A���t�@�l
		float transition_alpha_ = 1.0f;

		// Screen�J�ڂ̊�������
		float transition_complete_time_ = 0.3f;

		// Screen�J�ڂ̐F
		t2k::Color transition_color_ = t2k::Color(0);

		//====================================================================================================
		// �����o�֐�

		// ������
		void initialize(const int window_width, const int window_hieght, std::shared_ptr<Scene> first);
		
		// �X�V
		void update();
		
		// �I������
		void finalize();

		// Scene�J�ڌ�̃t�F�[�h�C��Sequence
		bool seqFadeIn();

		// Scene���s��Sequence
		bool seqIdle();

		// Scene�J�ڑO�̃t�F�[�h�A�E�gSequence
		bool seqFadeOut();

	public:
		~DxEngine() {}

		//====================================================================================================
		// �����o�֐�

		// �E�B���h�E�̕��̎擾
		inline int getWindowWidth() const { return window_width_; }

		// �E�B���h�E�̍����̎擾
		inline int getWindowHeight() const { return window_height_; }

		// ���݂̃V�[���̎擾
		inline std::shared_ptr<Scene> getNowScene() const { return now_scene_; }

		// Scene�J�ڂ̊������Ԃ�ݒ�
		inline void setTransitionCompleteTime(const float complete_time) { transition_complete_time_ = complete_time; }

		// Scene�J�ڂ̐F��ݒ�
		inline void setTransitionColor(const t2k::Color color) { transition_color_ = color; }

		// Scene�J�ڒ���
		inline bool isInTransition() const { return 0.0f < transition_alpha_; }

		// Scene���s���̌o�ߎ��Ԃ��擾
		// ���̊֐��Ŏ擾�ł��鎞�Ԃ�Scene�J�ڊ����ォ��̎��Ԃł�
		// Scene�J�ڒ���0.0f���߂�l�ƂȂ�܂�
		inline float getElapsedTimeForScene() const { return isInTransition() ? 0.0f : transition_sequence_.getProgressTime(); }

		// Scene�؂�ւ�
		// ���ۂɐ؂�ւ��̂̓g�����W�V�����I����
		inline void changeScene(std::shared_ptr<Scene> next, const float complete_time = 0.3f) {
			next_scene_ = next;
			setTransitionCompleteTime(complete_time);
			transition_sequence_.change(&DxEngine::seqFadeOut);
		}

		// Scene�I��
		// ���ۂɏI������̂̓g�����W�V�����I����
		inline void exitGame(const float complete_time = 0.3f) {
			setTransitionCompleteTime(complete_time);
			transition_sequence_.change(&DxEngine::seqFadeOut);
		}
	};

}
