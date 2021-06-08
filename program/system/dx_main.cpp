#include "DxLib.h"
#include "dx_main.h"
#include "../library/input.h"
#include "../library/mylib/time.h"
#include "../support/FrameRateController.h"
#include "../engine/dx_engine.h"
#include "../game/scene/logo.h"
#include "../game/save_data.h"


namespace sys {

	int DxMain::update() {

		const int WINDOW_WIDTH = 1024;
		const int WINDOW_HEIGHT = 768;
		const std::string WINDOW_NAME = "SPACE ESCAPE �`���z�n����E�o����I�`";
		const std::string FONT_PATH = "font/PixelMplus12-Regular.ttf";
		const std::string FONT_NAME = "PixelMplus12";

		// �t�H���g���\�[�X�̒ǉ�
		AddFontResourceEx(FONT_PATH.c_str(), FR_PRIVATE, NULL);
		ChangeFont(FONT_NAME.c_str(), DX_CHARSET_DEFAULT);
		ChangeFontType(DX_FONTTYPE_EDGE);

		// Window�̍���ɏo�Ă��閼�O�ύX
		SetWindowText(WINDOW_NAME.c_str());

		// �A�C�R���̐ݒ�
		SetWindowIconID(111);

		// Log.txt���o�͂��Ȃ�
		SetOutApplicationLogValidFlag(FALSE);

		// �E�B���h�E���[�h�ŋN��
		ChangeWindowMode(true);

		// �E�B���h�E�T�C�Y�ݒ�
		SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

		// �E�B���h�E����A�N�e�B�u���ł��������~�߂Ȃ��悤�ɂ���
		SetAlwaysRunFlag(true);

		// �t���[�����[�g�ݒ�
		FpsSetting(60, 800);

		// DX���C�u��������������
		// �G���[���N�����璼���ɏI��
		if (DxLib_Init() == -1) return -1;

		// �`���𗠉�ʂɕύX
		SetDrawScreen(DX_SCREEN_BACK);

		// ���Ԑ���̏�����
		mylib::Time::initialize();

		// �L�[���͐���̏�����
		t2k::Input::initialize();

		// �G���W���̏�����
		dxe::DxEngine& engine = dxe::DxEngine::getInstance();
		engine.initialize(WINDOW_WIDTH, WINDOW_HEIGHT, dxe::Scene::create<spe::Logo>());

		// �Z�[�u�f�[�^�̓ǂݍ���
		spe::SaveData& save_data = spe::SaveData::getInstance();
		save_data.initialize();

		// �T�E���h�}�l�[�W���[
		dxe::BGMManager& bgm_manager = dxe::BGMManager::getInstance();
		dxe::SEManager& se_manager = dxe::SEManager::getInstance();

		// ��ʂ��L���ɂȂ��čŏ��̃t���[����
		bool is_active_first_frame = false;

		// ���b�Z�[�W���[�v
		while (engine.is_playing_game_) {

			// ���Ԑ���X�V
			mylib::Time::update();

			// ���t���[���Ă�
			if (ProcessMessage() == -1) break;

			// �E�B���h�E����A�N�e�B�u�̏ꍇ�̓G���W���̍X�V���s��Ȃ�
			if (GetWindowActiveFlag() == false) {
				bgm_manager.stop();
				se_manager.stop();
				is_active_first_frame = true;
				continue;
			}

			// ��ʂ��L���ɂȂ�����ꎞ��~���Ă����T�E���h���Đ�����
			if (is_active_first_frame) {
				bgm_manager.playBackAll();
				se_manager.playBackAll();
				is_active_first_frame = false;
			}

			// ��ʂ��N���A
			ClearDrawScreen();

			// �L�[��Ԃ̍X�V
			t2k::Input::update();

			// �G���W���̍X�V
			engine.update();

			// �t���[�����[�g�R���g���[��
			FpsControll();

			// �o�b�N�o�b�t�@���t���b�v
			ScreenFlip();
			//SetWaitVSyncFlag(FALSE);
		}

		// �Z�[�u�f�[�^�̏�������
		save_data.finalize();

		// �G���W���̏I������
		engine.finalize();
		dxe::DxEngine::destroy();

		// �t�H���g���\�[�X�̉��
		RemoveFontResourceEx(FONT_PATH.c_str(), FR_PRIVATE, NULL);

		// DX���C�u�����g�p�̏I������
		DxLib_End();

		// �\�t�g�̏I��
		return 0;

	}

}
