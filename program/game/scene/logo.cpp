//--------------------------------------------------
// Scene
#include "logo.h"
#include "title.h"

//--------------------------------------------------
// Object

//--------------------------------------------------
// その他
#include "../object/debug_command.h"


namespace spe {

	void Logo::initialize() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		engine.setTransitionCompleteTime(TRANSITION_TIME);

		//----------------------------------------------------------------------------------------------------
		// スクリーン作成

		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		dxe::Camera2D::SharedPtr main_camera = dxe::Camera2D::create<dxe::Camera2D>();
		createScreenToScene("main_screen", main_camera, WINDOW_WIDTH, WINDOW_HEIGHT);

		//----------------------------------------------------------------------------------------------------
		// オブジェクト生成

		dxe::Sprite::createFromFile("graphics/logo/unitychan_logo.png");

		//----------------------------------------------------------------------------------------------------
		// デバッグコマンド有効化

		DebugCommand::create<DebugCommand>();
		t2k::Debug::log("Logo");

		//----------------------------------------------------------------------------------------------------
	}

	void Logo::lateUpdate() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		// シーン遷移中は入力を受け付けない
		if (engine.isInTransition()) return;

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C) || t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// ジョイパッド
		t2k::JoypadXInput* joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_A) || joypad->isPressButtonTrigger(t2k::JoypadXInput::BUTTON_B);
		}

		// 最大ロゴ表示時間
		const float IDLE_TIME_MAX = 2.0f;

		// 時間経過か入力でシーン切り替え
		if (IDLE_TIME_MAX < engine.getElapsedTimeForScene() || enter) {
			t2k::Debug::log("To Title");
			engine.changeScene(dxe::Scene::create<Title>(), TRANSITION_TIME);
		}
		
	}

	void Logo::finalize() {

	}

}
