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
		// インナークラス

		// アニメーションに対応するためのマップチップクラス
		class MapChip final : public t2k::SharedFactory<MapChip> {
		public:
			using SharedPtr = std::shared_ptr<MapChip>;
			std::vector<t2k::Texture::SharedPtr> textures_;
			int animation_index_ = 0;
			t2k::TimerFluct<int> animation_;
			float complete_time_ = 0.5f;
		};

		//====================================================================================================
		// メンバ定数

		inline static const int CODE_ITEM = 300;		// 生成コード：キーアイテム
		inline static const int CODE_PLANT = 200;		// 生成コード：植物
		inline static const int CODE_SLIME = 201;		// 生成コード：スライム
		inline static const int CODE_SKULL_UD = 202;	// 生成コード：どくろ（上下）
		inline static const int CODE_SKULL_LR = 203;	// 生成コード：どくろ（左右）
		inline static const int CODE_BIRD = 204;		// 生成コード：とり
		inline static const int CODE_WIZARD = 205;		// 生成コード：魔法使い
		inline static const int CODE_FLAME = 250;		// 生成コード：炎
		inline static const int CODE_POISON = 251;		// 生成コード：毒

		//====================================================================================================
		// メンバ変数

		int map_chip_size_ = 0;
		t2k::Vector3 offset_;
		std::vector<std::vector<int>> map_;
		std::unordered_map<int, MapChip::SharedPtr> map_chips_;

		//====================================================================================================
		// メンバ関数

		void update() final override;
		void render(std::shared_ptr<dxe::Screen> screen) final override;

		//====================================================================================================
	public:
		PlanetMap() {}
		~PlanetMap() {}

		//====================================================================================================
		// メンバ関数

		inline int getMapChipSize() const { return map_chip_size_; }
		inline int getMapWidth() const { return map_chip_size_ * map_[0].size(); }
		inline int getMapHeight() const { return map_chip_size_ * map_.size(); }

		//====================================================================================================
		// static関数

		static PlanetMap::SharedPtr create(const std::string& csv_folder_path, std::list<std::shared_ptr<PlanetWarpPoint>>& warp_points, std::shared_ptr<PlanetKeyItem>& key_item);

		//====================================================================================================
	};

}
