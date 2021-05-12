#pragma once
#include "../library/t2klib.h"


namespace dxe {

	// 補正方向列挙定数
	enum class CorrectDirection {
		NONE,	// 補正なし
		UP,		// 上に補正
		DOWN,	// 下に補正
		LEFT,	// 左に補正
		RIGHT	// 右に補正
	};

	// 衝突判定クラス
	// 生成されたColliisionObjectは自動的にこのクラスに登録されます
	// 衝突判定実行
	// 衝突判定矩形描画（デバッグ用）
	class CollisionManager final : public t2k::Singleton<CollisionManager> {
	private:
		// 基底クラスで生成するため
		friend class t2k::Singleton<CollisionManager>;
		// updatePrevPosition, collisionを呼ぶため
		friend class Scene;
		// renderDebugAreaを呼ぶため
		friend class Screen;
		// 生成とともにcollision_objects_に登録するため
		friend class CollisionObject;

		CollisionManager() {}

		//====================================================================================================
		// メンバ変数

		// CollisionObject一括管理用リスト
		std::list<std::shared_ptr<CollisionObject>> collision_objects_;

		//====================================================================================================
		// メンバ関数

		// update前のGameObjectの座標を更新
		void updatePrevPosition();

		// 衝突判定処理実行
		void collision();

		// 衝突判定矩形の描画（デバッグ用）
		void renderDebugArea(std::shared_ptr<Screen> screen) const;

		//====================================================================================================
	public:
		~CollisionManager() {}

		//====================================================================================================
		// メンバ変数

		// 衝突判定矩形の描画フラグ（デバッグ用）
		bool is_render_debug_area_ = false;

		//====================================================================================================
	};

}
