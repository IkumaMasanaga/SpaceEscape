#include "background_stars.h"


namespace spe {

	void BackgroundStars::update() {

		for (auto& sprite : star_sprites_) {
			if (sprite.animation_.isCompleteUpdate()) {
				sprite.animation_index_ = 0;
				sprite.animation_.setMethodLinear(&sprite.animation_index_, sprite.textures_.size(), sprite.complete_time_);
			}
		}

	}

	void BackgroundStars::render(std::shared_ptr<dxe::Screen> screen) {
		setBlendMode();

		for (const auto& star : stars_) {

			t2k::Transform t = getWorldTransform();
			t.position_ += star.transform_.position_;
			t2k::Transform ct = screen->getCamera2D()->getWorldTransform();
			float crs = screen->getCamera2D()->render_scale_;
			int sw = screen->getWidth() >> 1;
			int sh = screen->getHeight() >> 1;
			int rx = sw + (int)(((t.position_.x - ct.position_.x) * render_position_from_camera_) * crs);
			int ry = sh + (int)(((t.position_.y - ct.position_.y) * render_position_from_camera_) * crs);
			float scl = t.scale_ * crs * star.transform_.scale_;

			t2k::Texture::SharedPtr tex = star_sprites_[star.sprite_id_].textures_[star_sprites_[star.sprite_id_].animation_index_];

			// スクリーン範囲外ならば描画しない
			if (!t2k::isIntersectRect(t2k::Vector3((float)rx, (float)ry, 0), (int)(tex->getWidth() * scl), (int)(tex->getHeight() * scl), screen->getPosition() + t2k::Vector3((float)sw, (float)sh, 0), sw << 1, sh << 1)) continue;

			DrawRotaGraph(rx, ry, scl, t.rotation_, tex->getImage(), true);
		}

	}

	BackgroundStars::SharedPtr BackgroundStars::create(const BackgroundStarsDesc& desc) {
		BackgroundStars::SharedPtr ptr = dxe::RenderObject::create<BackgroundStars>();
		ptr->alpha_ = 0.5f;
		ptr->render_priority_ = desc.priority_;
		ptr->render_position_from_camera_ = desc.render_position_from_camera_;
		ptr->stars_.resize(desc.generate_num_);

		// 星の画像のロード
		std::vector<std::vector<std::string>> sd = t2k::loadCsv("data/stars.csv");
		ptr->star_sprites_.resize(sd.size());
		for (unsigned int i = 0; i < sd.size(); ++i) {
			ptr->star_sprites_[i].textures_ = t2k::Texture::createVectorFromFile(sd[i][1], std::stoi(sd[i][2]), std::stoi(sd[i][3]), std::stoi(sd[i][4]), std::stoi(sd[i][5]), std::stoi(sd[i][6]));
			ptr->star_sprites_[i].complete_time_ = t2k::randomRangeF(desc.animation_time_min_, desc.animation_time_max_);
			ptr->star_sprites_[i].animation_.setMethodLinear(&ptr->star_sprites_[i].animation_index_, ptr->star_sprites_[i].textures_.size(), ptr->star_sprites_[i].complete_time_);
		}

		// 星の位置を設定
		for (int i = 0; i < desc.generate_num_; ++i) {
			ptr->stars_[i].sprite_id_ = t2k::randomRangeI(0, sd.size());
			ptr->stars_[i].transform_.position_ = t2k::Vector3(t2k::randomRangeF((float)(-desc.width_ >> 1), (float)(desc.width_ >> 1)) / desc.render_position_from_camera_,
				t2k::randomRangeF((float)(-desc.height_ >> 1), (float)(desc.height_ >> 1)) / desc.render_position_from_camera_,
				0);
			ptr->stars_[i].transform_.scale_ = t2k::randomRangeF(desc.scale_min_, desc.scale_max_);
		}

		return ptr;
	}

}
