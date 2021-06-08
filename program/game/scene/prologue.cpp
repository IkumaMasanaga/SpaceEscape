//--------------------------------------------------
// Scene
#include "prologue.h"
#include "planet.h"

//--------------------------------------------------
// Object
#include "../object/render_object/background_stars.h"
#include "../object/mover/message_window.h"

//--------------------------------------------------
// ���̑�
//#include "../object/debug_command.h"

#include "../player_status.h"
#include "../timer.h"


namespace spe {

	void Prologue::initialize() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		//----------------------------------------------------------------------------------------------------
		// �X�N���[���쐬

		dxe::Camera2D::SharedPtr main_camera = dxe::Camera2D::create<dxe::Camera2D>();
		createScreenToScene("main_screen", main_camera, WINDOW_WIDTH, WINDOW_HEIGHT);

		//----------------------------------------------------------------------------------------------------
		// �I�u�W�F�N�g����

		// �w�i
		dxe::Sprite::SharedPtr bg = dxe::Sprite::createFromFile("graphics/bg_back.png");
		bg->alpha_ = 0.5f;

		// ��
		BackgroundStarsDesc bg_desc;
		bg_desc.generate_num_ = 50;
		bg_desc.width_ = WINDOW_WIDTH;
		bg_desc.height_ = WINDOW_HEIGHT;
		BackgroundStars::create(bg_desc);

		// ���z
		dxe::Sprite::SharedPtr sun = dxe::Sprite::createFromFile("graphics/space/00_sun.png");
		sun->transform_.position_ = t2k::Vector3((float)(-WINDOW_WIDTH >> 2), (float)(-WINDOW_HEIGHT >> 2), 0);

		// �f��
		dxe::Sprite::createFromFile("graphics/bg_planet.png");

		// �ڂ���
		dxe::Sprite::createFromFile("graphics/blur.png")->alpha_ = 0.4f;

		// Unity�����
		dxe::Sprite::createFromFile("graphics/unitychan/unitychan_2.png");

		// ���b�Z�[�W�E�B���h�E
		message_window_ = MessageWindow::createFromFile("text/prologue.txt");

		//----------------------------------------------------------------------------------------------------
		// �T�E���h

		// BGM
		dxe::BGMManager& bgm_manager = dxe::BGMManager::getInstance();
		bgm_manager.registBGM(dxe::BGMKey::PROLOGUE);
		bgm_manager.registBGM(dxe::BGMKey::PLAY1);
		bgm_manager.registBGM(dxe::BGMKey::PLAY2);

		// SE
		dxe::SEManager& se_manager = dxe::SEManager::getInstance();
		se_manager.registSE(dxe::SEKey::ENTER);
		se_manager.registSE(dxe::SEKey::BACK);

		// �Đ�
		bgm_manager.play(dxe::BGMKey::PROLOGUE);

		//----------------------------------------------------------------------------------------------------
		// �f�o�b�O�R�}���h�L����

		//DebugCommand::create<DebugCommand>();
		//t2k::Debug::log("Prologue");

		//----------------------------------------------------------------------------------------------------
	}

	void Prologue::lateUpdate() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		// �V�[���J�ڒ��͓��͂��󂯕t���Ȃ�
		if (engine.isInTransition()) return;

		bool enter = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C);
		bool back = t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_X);

		// �W���C�p�b�h
		mylib::JoypadXInput::SharedPtr joypad = dxe::JoypadManager::getInstance().getJoypad();
		if (joypad) {
			enter |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_A);
			back |= joypad->isPressButtonTrigger(mylib::JoypadXInput::BUTTON_B);
		}

		bool is_key_pressed = false;

		if (enter) {
			dxe::SEManager::getInstance().play(dxe::SEKey::ENTER);
			is_key_pressed = true;
		}
		if (back) {
			dxe::SEManager::getInstance().play(dxe::SEKey::BACK);
			is_key_pressed = true;
		}

		if (is_key_pressed) {
			PlayerStatus::destroy();
			Timer::destroy();
			engine.changeScene(Planet::create("prologue", "data/scene/planet/03_earth/a"));
			message_window_->close();
		}

	}

	void Prologue::finalize() {
		dxe::BGMManager& bgm_manager = dxe::BGMManager::getInstance();
		bgm_manager.stop();
		// �Đ�
		bgm_manager.play(dxe::BGMKey::PLAY1);
	}

}
