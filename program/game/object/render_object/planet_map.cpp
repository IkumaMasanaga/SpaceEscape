#include "planet_map.h"
#include "../collision_object/planet_warp_point.h"

#include "../collision_object/planet_key_item.h"
#include "../physics_object/enemy/planet_plant.h"
#include "../physics_object/enemy/planet_slime.h"
#include "../physics_object/enemy/planet_skull.h"
#include "../physics_object/enemy/planet_bird.h"
#include "../physics_object/enemy/planet_wizard.h"
#include "../physics_object/enemy/planet_flame.h"
#include "../physics_object/enemy/planet_poison.h"

#include "../../player_status.h"


namespace spe {

	void PlanetMap::update() {

		for (const auto& chip : map_chips_) {
			MapChip::SharedPtr mc = chip.second;
			if ((int)mc->textures_.size() <= 1) continue;
			if (mc->animation_.isCompleteUpdate()) {
				mc->animation_index_ = 0;
				mc->animation_.setMethodLinear(&mc->animation_index_, (int)mc->textures_.size(), mc->complete_time_);
			}
		}

	}

	void PlanetMap::render(std::shared_ptr<dxe::Screen> screen) {
		setBlendMode();

		for (int h = 0; h < (int)map_.size(); ++h) {
			for (int w = 0; w < (int)map_[h].size(); ++w) {
				std::unordered_map<int, MapChip::SharedPtr>::iterator it = map_chips_.find(map_[h][w]);
				if (it == map_chips_.end()) continue;

				t2k::Transform t = getWorldTransform();
				t.position_ += offset_ + t2k::Vector3((float)(w * map_chip_size_), (float)(h * map_chip_size_), 0);
				t2k::Transform ct = screen->getCamera2D()->getWorldTransform();
				float crs = screen->getCamera2D()->render_scale_;
				int sw = screen->getWidth() >> 1;
				int sh = screen->getHeight() >> 1;
				int rx = sw + (int)((t.position_.x - ct.position_.x * render_position_from_camera_) * crs);
				int ry = sh + (int)((t.position_.y - ct.position_.y * render_position_from_camera_) * crs);
				float scl = t.scale_ * crs;

				// �X�N���[���͈͊O�Ȃ�Ε`�悵�Ȃ�
				if (!t2k::isIntersectRect(t2k::Vector3((float)rx, (float)ry, 0), (int)(map_chip_size_ * scl), (int)(map_chip_size_ * scl), screen->getPosition() + t2k::Vector3((float)sw, (float)sh, 0), sw << 1, sh << 1)) continue;

				DrawRotaGraph(rx, ry, scl, t.rotation_, it->second->textures_[it->second->animation_index_]->getImage(), true);
			}
		}

	}

	PlanetMap::SharedPtr PlanetMap::create(const std::string& csv_folder_path, std::list<std::shared_ptr<PlanetWarpPoint>>& warp_points, std::shared_ptr<PlanetKeyItem>& key_item) {
		PlanetMap::SharedPtr ptr = dxe::RenderObject::create<PlanetMap>();

		/* �}�b�v�`�b�v�̃��[�h */ {
			std::vector<std::vector<std::string>> chip_data = t2k::loadCsv(csv_folder_path + "/../chip.csv");
			for (const auto& chip : chip_data) {
				int size = std::stoi(chip[6]);
				if (ptr->map_chip_size_ == 0) {
					ptr->map_chip_size_ = size;
				}
				MapChip::SharedPtr map_chip = MapChip::create<MapChip>();
				map_chip->textures_ = t2k::Texture::createVectorFromFile(chip[2], std::stoi(chip[3]), std::stoi(chip[4]), std::stoi(chip[5]), size, size);
				map_chip->complete_time_ = std::stof(chip[7]);
				map_chip->animation_.setMethodLinear(&map_chip->animation_index_, map_chip->textures_.size(), map_chip->complete_time_);
				ptr->map_chips_.try_emplace(std::stoi(chip[1]), map_chip);
			}
		}

		/* �}�b�v�̃��[�h */ {
			std::vector<std::vector<std::string>> md = t2k::loadCsv(csv_folder_path + "/map.csv");
			ptr->offset_ = t2k::Vector3((md[0].size() - 1) * ptr->map_chip_size_ * -0.5f, (md.size() - 1) * ptr->map_chip_size_ * -0.5f, 0);
			ptr->map_.resize(md.size());

			std::vector<std::vector<std::string>> wd = t2k::loadCsv(csv_folder_path + "/warp.csv");
			std::vector<std::vector<std::string>> id = t2k::loadCsv(csv_folder_path + "/item.csv");

			for (int h = 0; h < (int)md.size(); ++h) {
				ptr->map_[h].resize(md[h].size());
				for (int w = 0; w < (int)md[h].size(); ++w) {
					ptr->map_[h][w] = std::stoi(md[h][w]);

					const float X = (float)(ptr->offset_.x + w * ptr->map_chip_size_);
					const float Y = (float)(ptr->offset_.y + h * ptr->map_chip_size_);

					switch (ptr->map_[h][w]) {
					case CODE_ITEM:
						// ���łɃA�C�e�����l�����Ă����琶�����Ȃ�
						if (PlayerStatus::getInstance().hasItem((PlanetID)std::stoi(id[2][1]))) break;
						key_item = PlanetKeyItem::create(id[1][1], (PlanetID)std::stoi(id[2][1]), id[3][1]);
						key_item->transform_ = t2k::Transform(t2k::Vector3(X, Y, 0), 0.0f, 2.0f);
						break;
					case CODE_PLANT:
						PlanetPlant::create<PlanetPlant>()->transform_.position_ = t2k::Vector3(X, Y, 0);
						break;
					case CODE_SLIME:
						PlanetSlime::create<PlanetSlime>()->transform_.position_ = t2k::Vector3(X, Y, 0);
						break;
					case CODE_SKULL_UD:
						PlanetSkull::create(true)->transform_.position_ = t2k::Vector3(X, Y, 0);
						break;
					case CODE_SKULL_LR:
						PlanetSkull::create(false)->transform_.position_ = t2k::Vector3(X, Y, 0);
						break;
					case CODE_BIRD:
						PlanetBird::create<PlanetBird>()->transform_.position_ = t2k::Vector3(X, Y, 0);
						break;
					case CODE_WIZARD:
						PlanetWizard::create<PlanetWizard>()->transform_.position_ = t2k::Vector3(X, Y, 0);
						break;
					case CODE_FLAME:
						PlanetFlame::create(ptr->getMapWidth(), ptr->getMapHeight());
						break;
					case CODE_POISON:
						PlanetPoison::create(ptr->getMapWidth(), ptr->getMapHeight());
						break;
					default:
						// ���[�v�|�C���g�R�[�h�Ɠ����ꍇ�͐�������
						for (const auto& warp : wd) {
							if (md[h][w] != warp[1]) continue;
							PlanetWarpPoint::SharedPtr warp_ptr = PlanetWarpPoint::create(warp[2]);
							warp_ptr->transform_.position_ = t2k::Vector3(X, Y, 0);
							warp_points.emplace_back(warp_ptr);
							break;
						}
						break;
					}
				}
			}
		}

		/* �Փ˔����`�̐��� */ {
			dxe::CollisionObject::SharedPtr co = dxe::CollisionObject::create<dxe::CollisionObject>();
			co->update_priority_ = -FLT_MAX;
			ptr->pushChild(co);
			co->transform_.position_ = t2k::Vector3::ZERO;

			// �����蔻�肪�u����Ă��邩����t���O
			std::vector<std::vector<bool>> is_placed;
			is_placed.resize(ptr->map_.size());
			for (int h = 0; h < (int)is_placed.size(); ++h) {
				is_placed[h].resize(ptr->map_[h].size());
				for (int w = 0; w < (int)is_placed[h].size(); ++w) {
					is_placed[h][w] = false;
				}
			}

			for (int h = 0; h < (int)ptr->map_.size(); ++h) {
				for (int w = 0; w < (int)ptr->map_[h].size(); ++w) {

					// �����蔻��w��ł͂Ȃ����A���łɓ����蔻�肪�u����Ă���ꍇ�͎��̃Z����
					if (0 <= ptr->map_[h][w] || is_placed[h][w]) continue;

					// �����蔻��ݒu�J�n���W�̋L��
					const int START_INDEX_W = w;
					const int START_INDEX_H = h;

					// �͈͏I�����W�p�ϐ�
					int end_index_w = START_INDEX_W;
					int end_index_h = START_INDEX_H;

					// �܂�x�������i�������j�ɂ݂Ă���
					while (end_index_w < (int)ptr->map_[h].size()) {

						// �}�b�v�`�b�v���Ȃ����A���łɓ����蔻�肪�u����Ă���ꍇ�͏I��
						if (0 <= ptr->map_[h][end_index_w] || is_placed[h][end_index_w]) break;

						// �����蔻���u��
						is_placed[h][end_index_w] = true;

						// ���̗v�f��
						++end_index_w;
					}

					// x�������i�������j���I�������y�������i�c�����j��
					while (end_index_h < (int)ptr->map_.size()) {

						// ��d���[�v�𔲂���p
						bool is_break = false;

						// x�������i�������j�ւ݂Ă���
						for (int w2 = START_INDEX_W; w2 < end_index_w; ++w2) {

							// �}�b�v�`�b�v���Ȃ����A���݌��Ă��鍂�����X�^�[�g�ł͂Ȃ��ꍇ�ŁA���łɓ����蔻�肪�u����Ă���ꍇ�͏I���i��`�����Ȃ��j
							if (0 <= ptr->map_[end_index_h][w2] || (is_placed[end_index_h][w2] && !(end_index_h == START_INDEX_H))) {
								is_break = true;
								break;
							}

						}

						// ��`�����Ȃ������ꍇ�͏I��
						if (is_break) {
							break;
						}
						// ��`����ꂽ�ꍇ�͓����蔻���u��
						else {

							for (int w2 = START_INDEX_W; w2 < end_index_w; ++w2) {

								// �����蔻���u��
								is_placed[end_index_h][w2] = true;

							}

						}

						// ���̗v�f��
						++end_index_h;
					}

					// �����蔻��̕��ƍ������v�Z (�I�����W - �J�n���W) * �}�b�v�`�b�v�̃T�C�Y
					const int HIT_BOX_W = (end_index_w - START_INDEX_W) * ptr->map_chip_size_;
					const int HIT_BOX_H = (end_index_h - START_INDEX_H) * ptr->map_chip_size_;

					// �����蔻���u�����΍��W���v�Z (�J�n���W + (�I�����W - 1 - �J�n���W) * 0.5f) * �}�b�v�`�b�v�̃T�C�Y
					// (�I�����W - 1 - �J�n���W) * 0.5f �� �͈͂̔����i���S�j
					const int X = (int)((START_INDEX_W + (end_index_w - 1 - START_INDEX_W) * 0.5f) * ptr->map_chip_size_);
					const int Y = (int)((START_INDEX_H + (end_index_h - 1 - START_INDEX_H) * 0.5f) * ptr->map_chip_size_);

					// �����蔻���`�̒ǉ�
					co->addCollisionRect("map", dxe::CollisionRect::create(HIT_BOX_W, HIT_BOX_H, t2k::Vector3(ptr->offset_.x + X, ptr->offset_.y + Y, 0)));
				}
			}
		}

		return ptr;
	}

}
