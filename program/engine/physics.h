#pragma once
#include "../library/t2klib.h"


namespace dxe {

	// 物理演算クラス
	// 生成されたPhysicsObjectは自動的にこのクラスに登録されます
	// 物理演算処理実行
	// 重力の設定
	class Physics final : public mylib::Singleton<Physics> {
	private:
		// 基底クラスで生成するため
		friend class mylib::Singleton<Physics>;
		// updateを呼ぶため
		friend class Scene;
		// 生成とともにphysics_objects_に登録するため
		friend class PhysicsObject;

		Physics() {}

		//====================================================================================================
		// メンバ変数

		// PhysicsObject一括管理用リスト
		std::list<std::shared_ptr<PhysicsObject>> physics_objects_;

		//====================================================================================================
		// メンバ関数

		// 更新
		// 物理演算処理実行
		void update();

		//====================================================================================================
	public:
		~Physics() {}

		//====================================================================================================
		// メンバ変数

		// 重力
		t2k::Vector3 gravity_ = t2k::Vector3(0.0f, 9.81f, 0.0f);

		//====================================================================================================
	};

}
