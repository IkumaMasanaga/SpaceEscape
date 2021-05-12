#pragma once
#include "../../../engine/dxe.h"


namespace spe {

	enum class PlanetID;

	class PlanetKeyItem final : public dxe::CollisionObject {
	public:
		using SharedPtr = std::shared_ptr<PlanetKeyItem>;
		using WeakPtr = std::weak_ptr<PlanetKeyItem>;
	private:
		//====================================================================================================
		// メンバ変数

		// 画像のファイルパス
		std::string sprite_file_path_;

		// テキストのファイルパス
		std::string text_file_path_;

		// 惑星番号
		PlanetID planet_id_ = (PlanetID)0;

		//====================================================================================================
	public:
		PlanetKeyItem() {}
		~PlanetKeyItem() {}

		//====================================================================================================
		// メンバ関数

		// 画像のファイルパスの取得
		inline std::string getSpriteFilePath() const { return sprite_file_path_; }

		// テキストのファイルパスの取得
		inline std::string getTextFilePath() const { return text_file_path_; }

		// 惑星番号の取得
		inline PlanetID getPlanetID() const { return planet_id_; }

		//====================================================================================================
		// static関数

		// 生成
		static PlanetKeyItem::SharedPtr create(const std::string& sprite_path, const PlanetID planet_id, const std::string& text_path);

		//====================================================================================================
	};

}
