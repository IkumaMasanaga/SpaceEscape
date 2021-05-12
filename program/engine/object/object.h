#pragma once
#include <typeinfo>
#include "../../library/t2klib.h"


namespace dxe {

	// すべてのObjectの基底クラス
	// 生死確認
	// 名前の設定
	// 更新
	class Object : public t2k::SharedFactory<Object> {
	public:
		using SharedPtr = std::shared_ptr<Object>;
		using WeakPtr = std::weak_ptr<Object>;
	private:
		// シーン切り替え時にinstancs_count_を0に初期化するため
		friend class DxEngine;
		// shared_from_this_constructorを呼ぶため
		friend class t2k::SharedFactory<Object>;
		// 生成と同時にupdates_に登録するため
		friend class Scene;

		//====================================================================================================
		// メンバ変数

		// 名前
		std::string name_ = "unknown";

		// 生存フラグ
		bool is_alive_ = true;

		// 有効フラグ
		bool is_active_ = true;

		// Object唯一のインスタンスID
		unsigned int instance_id_;

		//====================================================================================================
		// static変数

		// Scene内で今まで生成してきたObjectの数
		inline static unsigned int instance_count_ = 0;

		//====================================================================================================
		// メンバ関数

		// shared_from_thisが使えるコンストラクタ（引数付き）
		void shared_from_this_constructor_exist_argument(std::any a) final override {}

		//====================================================================================================
	protected:
		//====================================================================================================
		// メンバ関数

		// shared_from_thisが使えるコンストラクタ
		virtual void shared_from_this_constructor() override;

		// 更新
		virtual void update() {}

		// 生成後に呼ばれる
		virtual void onCreated() {}

		//====================================================================================================
	public:
		Object() {
			instance_id_ = instance_count_;
			++instance_count_;
		}
		virtual ~Object() {}

		//====================================================================================================
		// メンバ変数

		// 更新優先度
		// 小さいほうが先に更新される
		float update_priority_ = 0.0f;

		// 常に更新するフラグ
		// 有効である限り更新される
		bool is_update_always_ = false;

		//====================================================================================================
		// メンバ関数

		// 名前の設定
		inline void setName(const std::string& name) { name_ = name; }

		// 自身の削除
		inline void destroy() { is_alive_ = false; }

		// 自身の有効フラグの設定
		inline void setActive(const bool is_active) { is_active_ = is_active; }

		// 名前の取得
		inline std::string getName() const { return name_; }

		// 生存フラグの取得
		inline bool isAlive() const { return is_alive_; }

		// 有効フラグの取得
		inline bool isActive() const { return is_active_; }

		// Object唯一のインスタンスIDの取得
		inline unsigned int getInstanceId() const { return instance_id_; }

		// クラス固有のIDの取得
		inline unsigned int getHashCode() const { return typeid(*this).hash_code(); }

		//====================================================================================================
		// static関数

		// Scene内で生成してきたObjectの総数を取得
		inline static unsigned int getInstanceCount() { return instance_count_; }

		// クラス固有のIDの取得
		template <class TObject>
		inline static unsigned int getHashCode() { return typeid(TObject).hash_code(); }

		//====================================================================================================
	};

}
