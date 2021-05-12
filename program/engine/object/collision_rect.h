#pragma once
#include "object.h"


namespace dxe {

	// 座標補正時の隙間
	class CorrectSpace final {
	public:
		CorrectSpace() {}
		CorrectSpace(const float up, const float down, const float left, const float right) : up_(up), down_(down), left_(left), right_(right) {}
		~CorrectSpace() {}
		
		//====================================================================================================
		// メンバ変数

		// 自身が上方向に補正されたときの隙間
		float up_ = 1.0f;

		// 自身が下方向に補正されたときの隙間
		float down_ = 1.0f;

		// 自身が左方向に補正されたときの隙間
		float left_ = 1.0f;

		// 自身が右方向に補正されたときの隙間
		float right_ = 1.0f;

		//====================================================================================================
	};
	
	// 衝突判定矩形1つのクラス
	class CollisionRect final : public Object {
	public:
		using SharedPtr = std::shared_ptr<CollisionRect>;
		using WeakPtr = std::weak_ptr<CollisionRect>;
	public:
		CollisionRect() {}
		~CollisionRect() {}

		//====================================================================================================
		// メンバ変数

		// transform_からの相対座標
		t2k::Vector3 center_ = t2k::Vector3::ZERO;

		// 幅
		int width_ = 32;

		// 高さ
		int height_ = 32;

		// トリガーフラグ
		bool is_trigger_ = false;

		// 補正フラグ
		bool is_correct_ = false;

		// 補正時の間隔
		CorrectSpace correct_space_;

		//====================================================================================================
		// static関数

		// 生成
		static CollisionRect::SharedPtr create(const int width, const int height, const t2k::Vector3& center = t2k::Vector3());

		//====================================================================================================
	};

}
