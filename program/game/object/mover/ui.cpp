#include "ui.h"
#include "ui_frame.h"
#include "../../player_status.h"
#include "../../timer.h"
#include "../../save_data.h"


namespace spe {

	void UI::update() {

		time_->changeText(t2k::formatToString("TIME: %.2f", Timer::getInstance().TIME));

		PlayerStatus& status = PlayerStatus::getInstance();

		// 現在のHPをみてUIに反映させる
		for (int i = 0; i < PlayerStatus::MAX_HP; ++i) {
			hp_sprites_[i]->changeTexture((i < status.getHP()) ? hp_ : hp_none_);
		}

		// エネルギーバーの長さを変更
		energy_bar_->width_ = (int)status.getEnergy();
		energy_bar_->transform_.position_.x = energy_start_x_ + (energy_bar_->width_ >> 1);

		// 仮消費エネルギーバーの長さを変更
		temp_energy_bar_->width_ = (int)status.getTempEnergy();
		temp_energy_bar_->transform_.position_.x = energy_start_x_ + energy_bar_->width_ - (temp_energy_bar_->width_ >> 1);

		// アイテムの有効フラグを変更
		for (int i = 0; i < planet_num_; ++i) {
			item_sprites_[i]->setActive(status.hasItem((PlanetID)i));
		}

	}

	UI::SharedPtr UI::create(const std::string& csv_folder) {

		//----------------------------------------------------------------------------------------------------

		// HP		STAGE		TIME
		// EG
		// 
		// 
		// 
		// ITEM					PAUSE

		//----------------------------------------------------------------------------------------------------

		dxe::DxEngine& engine = dxe::DxEngine::getInstance();

		// ウィンドウサイズ
		const int WINDOW_WIDTH = engine.getWindowWidth();
		const int WINDOW_HEIGHT = engine.getWindowHeight();
		const int WINDOW_WIDTH_HALF = WINDOW_WIDTH >> 1;
		const int WINDOW_HEIGHT_HALF = WINDOW_HEIGHT >> 1;

		// フォントサイズ
		const int FONT_SIZE = 24;
		const int FONT_SIZE_HALF = FONT_SIZE >> 1;

		// 描画優先度
		const float PRIORITY = 10.0f;

		// 描画位置
		const float LEFT_X = (float)(-WINDOW_WIDTH_HALF + FONT_SIZE_HALF);
		const float RIGHT_X = (float)(WINDOW_WIDTH_HALF - FONT_SIZE_HALF);
		const float TOP_Y = (float)(-WINDOW_HEIGHT_HALF + FONT_SIZE_HALF);
		const float BOTTOM_Y = (float)(WINDOW_HEIGHT_HALF - FONT_SIZE_HALF);

		UI::SharedPtr ptr = dxe::Mover::create<UI>();

		//----------------------------------------------------------------------------------------------------
		// HP
		dxe::Text::SharedPtr hp = dxe::Text::create("HP:");
		hp->transform_.position_ = t2k::Vector3(LEFT_X, TOP_Y, 0.0f);
		hp->render_priority_ = PRIORITY;
		hp->render_position_from_camera_ = 0.0f;
		hp->align_mode_x_ = dxe::AlignModeX::LEFT;
		hp->align_mode_y_ = dxe::AlignModeY::TOP;
		hp->font_size_ = FONT_SIZE;
		ptr->pushChild(hp);

		// HPの画像
		ptr->hp_ = t2k::Texture::createFromFile("graphics/ui/hp.png");
		ptr->hp_none_ = t2k::Texture::createFromFile("graphics/ui/hp_none.png");

		const float HP_START_X = LEFT_X + (FONT_SIZE * 2) + FONT_SIZE_HALF;
		const float INTERVAL = (float)(ptr->hp_->getWidth() + 5);

		ptr->hp_sprites_.resize(PlayerStatus::MAX_HP);

		for (int i = 0; i < PlayerStatus::MAX_HP; ++i) {
			dxe::Sprite::SharedPtr sprite = dxe::Sprite::createFromTexture(ptr->hp_);
			sprite->transform_.position_ = t2k::Vector3(HP_START_X + (INTERVAL * i), TOP_Y + FONT_SIZE_HALF, 0.0f);
			sprite->render_priority_ = PRIORITY;
			sprite->render_position_from_camera_ = 0.0f;
			ptr->hp_sprites_[i] = sprite;
		}

		//----------------------------------------------------------------------------------------------------
		// ENERGY
		const float ENERGY_Y = TOP_Y + FONT_SIZE + FONT_SIZE_HALF;

		dxe::Text::SharedPtr enegy = dxe::Text::create("EG:");
		enegy->transform_.position_ = t2k::Vector3(LEFT_X, ENERGY_Y, 0.0f);
		enegy->render_priority_ = PRIORITY;
		enegy->render_position_from_camera_ = 0.0f;
		enegy->align_mode_x_ = dxe::AlignModeX::LEFT;
		enegy->align_mode_y_ = dxe::AlignModeY::TOP;
		enegy->font_size_ = FONT_SIZE;
		ptr->pushChild(enegy);

		// 枠の厚み
		const int FLAME_THICKNESS = 4;

		// フレームとエネルギー
		UIFrameDesc energy_desc;
		energy_desc.width_ = (int)PlayerStatus::MAX_ENERGY + FLAME_THICKNESS;
		energy_desc.height_ = FONT_SIZE;
		energy_desc.interval_ = FLAME_THICKNESS >> 1;
		energy_desc.render_position_from_camera_ = 0.0f;
		energy_desc.inner_color_ = t2k::Color(0.5f);
		energy_desc.is_open_ = true;

		UIFrame::SharedPtr energy_frame = UIFrame::create(energy_desc);
		energy_frame->transform_.position_ = t2k::Vector3(HP_START_X - (FONT_SIZE_HALF / 2) + (PlayerStatus::MAX_ENERGY / 2), ENERGY_Y + FONT_SIZE_HALF, 0.0f);
		energy_frame->setRenderPriority(PRIORITY);
		ptr->pushChild(energy_frame);

		ptr->energy_start_x_ = HP_START_X - (FONT_SIZE_HALF / 2);

		ptr->energy_bar_ = dxe::RectRenderer::create(0, energy_desc.height_ - FLAME_THICKNESS, t2k::Color(0.0f, 0.6f, 1.0f));
		ptr->energy_bar_->transform_.position_ = t2k::Vector3(ptr->energy_start_x_, ENERGY_Y + FONT_SIZE_HALF, 0.0f);
		ptr->energy_bar_->render_priority_ = PRIORITY;
		ptr->energy_bar_->render_position_from_camera_ = 0.0f;
		ptr->pushChild(ptr->energy_bar_);

		// 仮消費エネルギーバー
		ptr->temp_energy_bar_ = dxe::RectRenderer::create(0, energy_desc.height_ - FLAME_THICKNESS, t2k::Color(1.0f));
		ptr->temp_energy_bar_->transform_.position_ = t2k::Vector3(ptr->energy_start_x_, ENERGY_Y + FONT_SIZE_HALF, 0.0f);
		ptr->temp_energy_bar_->alpha_ = 0.5f;
		ptr->temp_energy_bar_->render_priority_ = PRIORITY;
		ptr->temp_energy_bar_->render_position_from_camera_ = 0.0f;
		ptr->pushChild(ptr->temp_energy_bar_);

		//----------------------------------------------------------------------------------------------------
		// STAGE
		dxe::Text::SharedPtr stage = dxe::Text::createFromFile(csv_folder + "/stage.txt");
		stage->transform_.position_ = t2k::Vector3(0.0f, TOP_Y, 0.0f);
		stage->render_priority_ = PRIORITY;
		stage->render_position_from_camera_ = 0.0f;
		stage->align_mode_x_ = dxe::AlignModeX::CENTER;
		stage->align_mode_y_ = dxe::AlignModeY::TOP;
		stage->font_size_ = FONT_SIZE;
		ptr->pushChild(stage);

		//----------------------------------------------------------------------------------------------------
		// TIME
		ptr->time_ = dxe::Text::create("TIME: ");
		ptr->time_->transform_.position_ = t2k::Vector3(RIGHT_X, TOP_Y, 0.0f);
		ptr->time_->render_priority_ = PRIORITY;
		ptr->time_->render_position_from_camera_ = 0.0f;
		ptr->time_->align_mode_x_ = dxe::AlignModeX::RIGHT;
		ptr->time_->align_mode_y_ = dxe::AlignModeY::TOP;
		ptr->time_->font_size_ = FONT_SIZE;
		ptr->pushChild(ptr->time_);

		//----------------------------------------------------------------------------------------------------
		// ITEM
		dxe::Text::SharedPtr item_text = dxe::Text::create("ITEM:");
		item_text->transform_.position_ = t2k::Vector3(LEFT_X, BOTTOM_Y, 0.0f);
		item_text->render_priority_ = PRIORITY;
		item_text->render_position_from_camera_ = 0.0f;
		item_text->align_mode_x_ = dxe::AlignModeX::LEFT;
		item_text->align_mode_y_ = dxe::AlignModeY::BOTTOM;
		item_text->font_size_ = FONT_SIZE;
		ptr->pushChild(item_text);

		SaveData& save_data = SaveData::getInstance();
		ptr->planet_num_ = (save_data.isClearEnd(EndType::GOOD_SURVIVAL)) ? SaveData::PLANET_MAX : SaveData::PLANET_MAX - 1;

		ptr->item_sprites_.resize(ptr->planet_num_);

		// アイテムのファイルパス
		const std::string ITEM_FILE_PATH[SaveData::PLANET_MAX] = {
			"graphics/item/00.png",
			"graphics/item/01.png",
			"graphics/item/02.png",
			"graphics/item/03.png",
			"graphics/item/04.png",
			"graphics/item/05.png",
			"graphics/item/06.png",
			"graphics/item/07.png",
			"graphics/item/08.png",
			"graphics/item/09.png",
		};

		// 枠
		UIFrameDesc item_desc;
		item_desc.width_ = FONT_SIZE;
		item_desc.height_ = FONT_SIZE;
		item_desc.interval_ = 2;
		item_desc.render_position_from_camera_ = 0.0f;
		item_desc.inner_color_ = t2k::Color(0.5f);
		item_desc.is_open_ = true;

		const float ITEM_START_X = LEFT_X + (FONT_SIZE * 4);

		for (int i = 0; i < ptr->planet_num_; ++i) {

			// 枠
			UIFrame::SharedPtr item_frame = UIFrame::create(item_desc);
			item_frame->transform_.position_ = t2k::Vector3(ITEM_START_X + (FONT_SIZE_HALF * 2.5f * i), BOTTOM_Y - FONT_SIZE_HALF, 0.0f);
			item_frame->setRenderPriority(PRIORITY);
			ptr->pushChild(item_frame);

			// アイテム
			dxe::Sprite::SharedPtr item = dxe::Sprite::createFromFile(ITEM_FILE_PATH[i]);
			item->transform_.position_ = t2k::Vector3(ITEM_START_X + (FONT_SIZE_HALF * 2.5f * i), BOTTOM_Y - FONT_SIZE_HALF, 0.0f);
			item->render_priority_ = PRIORITY;
			item->render_position_from_camera_ = 0.0f;
			ptr->item_sprites_[i] = item;
			ptr->pushChild(ptr->item_sprites_[i]);
		}

		//----------------------------------------------------------------------------------------------------
		// PAUSE
		dxe::Text::SharedPtr pause = dxe::Text::create("[ SPACE ] PAUSE");
		pause->transform_.position_ = t2k::Vector3(RIGHT_X, BOTTOM_Y, 0.0f);
		pause->render_priority_ = PRIORITY;
		pause->render_position_from_camera_ = 0.0f;
		pause->align_mode_x_ = dxe::AlignModeX::RIGHT;
		pause->align_mode_y_ = dxe::AlignModeY::BOTTOM;
		pause->font_size_ = FONT_SIZE;
		ptr->pushChild(pause);
		
		//----------------------------------------------------------------------------------------------------

		return ptr;

	}

}
