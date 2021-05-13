//--------------------------------------------------
// Scene
#include "logo.h"
#include "title.h"

//--------------------------------------------------
// Object

//--------------------------------------------------
// ���̑�
#include "../object/debug_command.h"


namespace spe {

	void Logo::initialize() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		engine.setTransitionCompleteTime(TRANSITION_TIME);

		//----------------------------------------------------------------------------------------------------
		// �X�N���[���쐬

		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		dxe::Camera2D::SharedPtr main_camera = dxe::Camera2D::create<dxe::Camera2D>();
		createScreenToScene("main_screen", main_camera, WINDOW_WIDTH, WINDOW_HEIGHT);

		//----------------------------------------------------------------------------------------------------
		// �I�u�W�F�N�g����

		dxe::Sprite::createFromFile("graphics/logo/unitychan_logo.png");

		//----------------------------------------------------------------------------------------------------
		// �f�o�b�O�R�}���h�L����

		DebugCommand::create<DebugCommand>();
		t2k::Debug::log("Logo");

		//----------------------------------------------------------------------------------------------------
	}

	void Logo::lateUpdate() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		// �V�[���J�ڒ��͓��͂��󂯕t���Ȃ�
		if (engine.isInTransition()) return;

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C) || t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// �W���C�p�b�h
		t2k::JoypadXInput* joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_A) || joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_B);
		}

		// �ő働�S�\������
		const float IDLE_TIME_MAX = 2.0f;

		// ���Ԍo�߂����͂ŃV�[���؂�ւ�
		if (IDLE_TIME_MAX < engine.getElapsedTimeForScene() || enter) {
			t2k::Debug::log("To Title");
			engine.changeScene(dxe::Scene::create<Title>(), TRANSITION_TIME);
		}
		
	}

	void Logo::finalize() {

	}

}
