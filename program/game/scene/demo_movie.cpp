//--------------------------------------------------
// Scene
#include "demo_movie.h"
#include "logo.h"

//--------------------------------------------------
// Object
#include "../object/mover/ui_frame.h"

//--------------------------------------------------
// その他
//#include "../object/debug_command.h"


namespace spe {

	void DemoMovie::initialize() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		//----------------------------------------------------------------------------------------------------
		// スクリーン作成

		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();

		dxe::Camera2D::SharedPtr main_camera = dxe::Camera2D::create<dxe::Camera2D>();
		createScreenToScene("main_screen", main_camera, WINDOW_WIDTH, WINDOW_HEIGHT);

		//----------------------------------------------------------------------------------------------------
		// オブジェクト生成

		// 外部ファイルから読み込み
		std::vector<std::vector<std::string>> data = t2k::loadCsv("data/movie/movie.csv");
		movie_ = dxe::MovieSprite::createFromFile(data[movie_num_][0]);
		movie_->setVolume(std::stof(data[movie_num_][1]));
		movie_->play();

		// 次の動画へ
		++movie_num_;
		movie_num_ %= data.size();

		// 枠
		UIFrameDesc desc;
		desc.width_ = 300;
		desc.height_ = 50;
		desc.inner_color_.set(0.5f);
		desc.is_open_ = true;

		// テキスト
		const int FONT_SIZE = 30;
		const float Y = 300.0f;
		
		UIFrame::SharedPtr demo_frame = UIFrame::create(desc);
		dxe::Text::SharedPtr demo_text = dxe::Text::create("DEMO MOVIE");
		demo_frame->pushChild(demo_text);
		demo_text->align_mode_x_ = dxe::AlignModeX::CENTER;
		demo_text->align_mode_y_ = dxe::AlignModeY::MIDDLE;
		demo_text->font_size_ = FONT_SIZE;

		UIFrame::SharedPtr press_frame = UIFrame::create(desc);
		dxe::Text::SharedPtr press_text = dxe::Text::create("PRESS ANY KEY");
		press_frame->pushChild(press_text);
		press_text->align_mode_x_ = dxe::AlignModeX::CENTER;
		press_text->align_mode_y_ = dxe::AlignModeY::MIDDLE;
		press_text->font_size_ = FONT_SIZE;

		demo_frame->transform_.position_.y = -Y;
		press_frame->transform_.position_.y = Y;

		//----------------------------------------------------------------------------------------------------
		// デバッグコマンド有効化

		//DebugCommand::create<DebugCommand>();
		//t2k::Debug::log("DemoMovie");

		//----------------------------------------------------------------------------------------------------
	}

	void DemoMovie::lateUpdate() {

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		// シーン遷移中は処理しない
		if (engine.isInTransition()) return;

		// 何かキーが押されるか動画が終了したらロゴへ
		if ((CheckHitKeyAll() != 0) || (!movie_->isPlaying())) {
			engine.changeScene(dxe::Scene::create<Logo>());
		}
	}

	void DemoMovie::finalize() {

	}

}
