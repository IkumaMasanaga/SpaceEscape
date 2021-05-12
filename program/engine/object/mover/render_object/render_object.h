#pragma once
#include "../mover.h"


namespace dxe {

	// ブレンドモード
	enum class BlendMode {
		ALPHA,	// アルファブレンド
		ADD,	// 加算ブレンド
		SUB,	// 減算ブレンド
		MUL		// 乗算ブレンド
	};

	// 描画するObject
	class RenderObject : public Mover {
	public:
		using SharedPtr = std::shared_ptr<RenderObject>;
		using WeakPtr = std::weak_ptr<RenderObject>;
	private:
		// renderを呼ぶため
		friend class Screen;
		// shared_from_this_constructorを呼ぶため
		friend class t2k::SharedFactory<Object>;

		//====================================================================================================
		// メンバ変数

		// 描画フラグ
		// 描画はしないけど更新はしたい際に使用する
		bool is_render_ = true;

		//====================================================================================================
	protected:
		//====================================================================================================
		// メンバ関数

		// shared_from_thisが使えるコンストラクタ
		virtual void shared_from_this_constructor() override;

		// 描画
		virtual void render(std::shared_ptr<Screen> screen) = 0;

		//====================================================================================================
	public:
		RenderObject() {}
		virtual ~RenderObject() {}

		//====================================================================================================
		// メンバ変数

		// 描画優先度
		// 小さいほうが先に描画される
		float render_priority_ = 0.0f;

		// アルファ値
		float alpha_ = 1.0f;

		// ブレンドモード
		BlendMode blend_mode_ = BlendMode::ALPHA;

		// 描画するときのカメラからの距離の割合
		// この値を変更して変わるのは描画の位置だけです（衝突判定矩形の位置は変わらない）
		float render_position_from_camera_ = 1.0f;

		//====================================================================================================
		// メンバ関数

		// ブレンドモードの設定
		// 描画前に呼ぶ
		void setBlendMode() const;

		// 描画フラグの設定
		inline void setRender(const bool is_render) { is_render_ = is_render; }

		// 描画フラグの取得
		inline bool isRender() const { return is_render_; }

		//====================================================================================================
	};

}
