#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class PlanetWarpPoint;
	class PlanetKeyItem;

	class PlanetMap final : public dxe::RenderObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetMap>;
		using WeakPtr = std::weak_ptr<PlanetMap>;
	private:
		//====================================================================================================
		// �C���i�[�N���X

		// �A�j���[�V�����ɑΉ����邽�߂̃}�b�v�`�b�v�N���X
		class MapChip final : public t2k::SharedFactory<MapChip> {
		public:
			using SharedPtr = std::shared_ptr<MapChip>;
			std::vector<t2k::Texture::SharedPtr> textures_;
			int animation_index_ = 0;
			t2k::TimerFluct<int> animation_;
			float complete_time_ = 0.5f;
		};

		//====================================================================================================
		// �����o�萔

		inline static const int CODE_ITEM = 300;		// �����R�[�h�F�L�[�A�C�e��
		inline static const int CODE_PLANT = 200;		// �����R�[�h�F�A��
		inline static const int CODE_SLIME = 201;		// �����R�[�h�F�X���C��
		inline static const int CODE_SKULL_UD = 202;	// �����R�[�h�F�ǂ���i�㉺�j
		inline static const int CODE_SKULL_LR = 203;	// �����R�[�h�F�ǂ���i���E�j
		inline static const int CODE_BIRD = 204;		// �����R�[�h�F�Ƃ�
		inline static const int CODE_WIZARD = 205;		// �����R�[�h�F���@�g��
		inline static const int CODE_FLAME = 250;		// �����R�[�h�F��
		inline static const int CODE_POISON = 251;		// �����R�[�h�F��

		//====================================================================================================
		// �����o�ϐ�

		int map_chip_size_ = 0;
		t2k::Vector3 offset_;
		std::vector<std::vector<int>> map_;
		std::unordered_map<int, MapChip::SharedPtr> map_chips_;

		//====================================================================================================
		// �����o�֐�

		void update() final override;
		void render(std::shared_ptr<dxe::Screen> screen) final override;

		//====================================================================================================
	public:
		PlanetMap() {}
		~PlanetMap() {}

		//====================================================================================================
		// �����o�֐�

		inline int getMapChipSize() const { return map_chip_size_; }
		inline int getMapWidth() const { return map_chip_size_ * map_[0].size(); }
		inline int getMapHeight() const { return map_chip_size_ * map_.size(); }

		//====================================================================================================
		// static�֐�

		static PlanetMap::SharedPtr create(const std::string& csv_folder_path, std::list<std::shared_ptr<PlanetWarpPoint>>& warp_points, std::shared_ptr<PlanetKeyItem>& key_item);

		//====================================================================================================
	};

}
