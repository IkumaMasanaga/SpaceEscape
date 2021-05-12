#include <algorithm>
#include "../engine/dxe.h"
#include "save_data.h"
#include "timer.h"


namespace spe {

	void SaveData::initialize() {
		reset();
		load();
		dxe::BGMManager::getInstance().setMasterVolume(bgm_volume_);
		dxe::SEManager::getInstance().setMasterVolume(se_volume_);
	}

	void SaveData::finalize() {
		save();
	}

	float* SaveData::recordGoodRanking(const EndType end_type, const float clear_time) {

		// 記録するランキングのポインタを取得
		float* ranking = nullptr;
		switch (end_type) {
		case EndType::GOOD_NEW_WORLD:
			ranking = good_new_world_ranking_;
			break;
		case EndType::GOOD_SURVIVAL:
			ranking = good_survival_ranking_;
			break;
		// GOODエンド以外は記録しない
		default:
			return nullptr;
		}

		// 3位の記録よりも速ければ更新
		if (ranking[2] <= clear_time) return ranking;
		ranking[2] = clear_time;
		// ソート
		for (int a = 0; a < 2; ++a) {
			for (int b = a + 1; b < 3; ++b) {
				if (ranking[a] > ranking[b]) {
					float tmp = ranking[a];
					ranking[a] = ranking[b];
					ranking[b] = tmp;
				}
			}
		}

		return ranking;
	}

	void SaveData::save() {
		FILE* fp = nullptr;
		fopen_s(&fp, "data/play_status.bin", "wb");
		if (!fp) return;

		fwrite(&clear_ends_, sizeof(int), 1, fp);
		fwrite(&get_items_, sizeof(int), 1, fp);
		fwrite(&bgm_volume_, sizeof(float), 1, fp);
		fwrite(&se_volume_, sizeof(float), 1, fp);
		fwrite(good_new_world_ranking_, sizeof(float), 3, fp);
		fwrite(good_survival_ranking_, sizeof(float), 3, fp);

		fclose(fp);

		return;
	}

	void SaveData::load() {
		FILE* fp = nullptr;
		fopen_s(&fp, "data/play_status.bin", "rb");
		if (!fp) return;

		fread(&clear_ends_, sizeof(int), 1, fp);
		fread(&get_items_, sizeof(int), 1, fp);
		fread(&bgm_volume_, sizeof(float), 1, fp);
		fread(&se_volume_, sizeof(float), 1, fp);
		fread(good_new_world_ranking_, sizeof(float), 3, fp);
		fread(good_survival_ranking_, sizeof(float), 3, fp);

		fclose(fp);

		return;
	}

	dxe::Mover::SharedPtr SaveData::createRankingText(const EndType end_type, const float clear_time) {

		// 記録出来なかったら終了
		float* ranking = recordGoodRanking(end_type, clear_time);
		if (!ranking) return nullptr;

		const int FONT_SIZE = 30;
		const int INTERVAL = 10;

		dxe::Mover::SharedPtr ret = dxe::Mover::create<dxe::Mover>();

		// 今のプレイのクリアタイム
		dxe::Text::SharedPtr time_text = dxe::Text::create("CLEAR TIME");
		ret->pushChild(time_text);
		time_text->transform_.position_ = t2k::Vector3(0.0f, -100.0f, 0.0f);
		time_text->font_size_ = FONT_SIZE;

		dxe::Text::SharedPtr clear_time_text = dxe::Text::create(t2k::formatToString("   [ %.2f ]", clear_time));
		ret->pushChild(clear_time_text);
		clear_time_text->transform_.position_ = t2k::Vector3(0.0f, -100.0f + (FONT_SIZE + INTERVAL) * 1, 0.0f);
		clear_time_text->font_size_ = FONT_SIZE;

		// ランキング
		dxe::Text::SharedPtr ranking_text = dxe::Text::create("RANKING");
		ret->pushChild(ranking_text);
		ranking_text->transform_.position_ = t2k::Vector3(0.0f, -100.0f + (FONT_SIZE + INTERVAL) * 3, 0.0f);
		ranking_text->font_size_ = FONT_SIZE;

		// 赤色に塗り替えたか
		bool is_color_red = false;

		for (int i = 0; i < 3; ++i) {
			dxe::Text::SharedPtr t = dxe::Text::create(ranking[i] == Timer::TIME_LIMIT ? t2k::formatToString("   %d. ------", i + 1) : t2k::formatToString("   %d. %.2f", i + 1, ranking[i]));
			ret->pushChild(t);
			t->transform_.position_ = t2k::Vector3(0.0f, -100.0f + (FONT_SIZE + INTERVAL) * (4 + i), 0.0f);
			t->font_size_ = FONT_SIZE;

			// 今回クリアしたタイムの場合は色を変える
			if (!is_color_red && ranking[i] == clear_time) {
				t->color_.set(1.0f, 0.0f, 0.0f);
				is_color_red = true;
			}
		}

		return ret;

	}

	dxe::Mover::SharedPtr SaveData::createRankingText(const EndType end_type) {

		const int FONT_SIZE = 24;
		const int INTERVAL = 10;

		dxe::Mover::SharedPtr ret = dxe::Mover::create<dxe::Mover>();

		float* ranking = nullptr;
		switch (end_type) {
		case EndType::GOOD_NEW_WORLD:
			ranking = good_new_world_ranking_;
			break;
		case EndType::GOOD_SURVIVAL:
			ranking = good_survival_ranking_;
			break;
			// GOODエンド以外は終了
		default:
			return nullptr;
		}

		for (int i = 0; i < 3; ++i) {
			dxe::Text::SharedPtr t = dxe::Text::create(ranking[i] == Timer::TIME_LIMIT ? t2k::formatToString("   %d. ------", i + 1) : t2k::formatToString("   %d. %.2f", i + 1, ranking[i]));
			ret->pushChild(t);
			t->transform_.position_.y = (float)((FONT_SIZE + INTERVAL) * i);
			t->font_size_ = FONT_SIZE;
			t->align_mode_x_ = dxe::AlignModeX::LEFT;
			t->align_mode_y_ = dxe::AlignModeY::MIDDLE;
		}

		return ret;

	}

	void SaveData::reset() {
		clear_ends_ = 0;
		get_items_ = 0;
		for (int i = 0; i < 3; ++i) {
			good_new_world_ranking_[i] = Timer::TIME_LIMIT;
			good_survival_ranking_[i] = Timer::TIME_LIMIT;
		}
	}

	void SaveData::changeBGMVolume(const float change_value) {
		bgm_volume_ += change_value;
		bgm_volume_ = std::clamp(bgm_volume_, 0.0f, 1.0f);
		dxe::BGMManager::getInstance().setMasterVolume(bgm_volume_);
	}

	void SaveData::changeSEVolume(const float change_value) {
		se_volume_ += change_value;
		se_volume_ = std::clamp(se_volume_, 0.0f, 1.0f);
		dxe::SEManager::getInstance().setMasterVolume(se_volume_);
	}

}
