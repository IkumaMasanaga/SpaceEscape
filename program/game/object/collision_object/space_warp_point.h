#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	class SpaceWarpPoint final : public dxe::CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<SpaceWarpPoint>;
		using WeakPtr = std::weak_ptr<SpaceWarpPoint>;
	private:
		//====================================================================================================
		// メンバ変数

		// ワープ先のCSVフォルダ
		std::string warp_csv_folder_;

		// 惑星の画像
		dxe::Sprite::SharedPtr planet_ = nullptr;

		// ワープ画像
		dxe::AnimationSprite::SharedPtr warp_ = nullptr;

		// キー画像
		dxe::AnimationSprite::SharedPtr key_ = nullptr;

		// シーンへワープシグナルを飛ばす用
		bool is_warp_ = false;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update() final override;

		// 衝突時
		void onCollision(CollisionObject::SharedPtr other, std::shared_ptr<dxe::CollisionRect> rect, const dxe::CorrectDirection direction) final override;

		//====================================================================================================
	public:
		SpaceWarpPoint() {}
		~SpaceWarpPoint() {}

		//====================================================================================================
		// メンバ関数

		// ワープ先のCSVファイルのパス
		inline std::string getWarpDestination() const { return warp_csv_folder_; }

		// シーンへシグナルを飛ばす用
		inline bool isWarp() const { return is_warp_; }

		//====================================================================================================
		// static関数

		// 生成
		static SpaceWarpPoint::SharedPtr create(const std::string& csv_folder);

		//====================================================================================================
	};

}
