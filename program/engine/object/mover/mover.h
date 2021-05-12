#pragma once
#include "../object.h"


namespace dxe {

	class Mover : public Object {
	public:
		using SharedPtr = std::shared_ptr<Mover>;
		using WeakPtr = std::weak_ptr<Mover>;
	private:
		//====================================================================================================
		// メンバ変数

		// 自身の親
		Mover::WeakPtr parent_;

		// 自身を子としたときの前
		Mover::WeakPtr prev_;

		// 自身を子としたときの次
		Mover::WeakPtr next_;

		// 自身を親としたときの子の先頭
		Mover::WeakPtr child_;

		//====================================================================================================
		// メンバ関数

		// 指定したTransformが自身をルートとして存在するか
		bool isExistence(Mover::SharedPtr transform) const;

		// 自身を子として先頭の子の取得
		Mover::SharedPtr getFront();

		// 自身を子として最後の子の取得
		Mover::SharedPtr getBack();

		// 自身を子として前の子の取得
		inline Mover::SharedPtr getPrev() const { return (prev_.expired()) ? nullptr : prev_.lock(); }

		// 自身を子として次の子の取得
		inline Mover::SharedPtr getNext() const { return (next_.expired()) ? nullptr : next_.lock(); }

		//====================================================================================================
	protected:

	public:
		Mover() {}
		virtual ~Mover() {}

		//====================================================================================================
		// メンバ変数

		// 座標、回転、拡大率
		t2k::Transform transform_;

		//====================================================================================================
		// メンバ関数

		// 親の取得
		inline Mover::SharedPtr getParent() const { return (parent_.expired()) ? nullptr : parent_.lock(); }

		// 子の取得
		// 先頭から数えた数値を指定
		Mover::SharedPtr getChild(const int count) const;

		// 自身の直下の子の数を取得
		int getChildCount() const;

		// 最終的なTransformの設定
		void setWorldTransform(const t2k::Transform& transform);

		// 最終的なワールド座標の取得
		t2k::Transform getWorldTransform() const;

		// ワールド座標からローカル座標に変換
		t2k::Vector3 toLocalPosition(const t2k::Vector3& world_position);

		// 子を最後尾に追加
		void pushChild(Mover::SharedPtr child);

		// 自身が親から離脱
		void popParent();

		// 自身と子供の有効状態を変更
		void setActiveWithChild(const bool is_active);

		// 自身と子供をすべて消す
		void destroyWithChild();

		//====================================================================================================
	};

}
