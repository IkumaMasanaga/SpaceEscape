#pragma once


namespace t2k {

	// 各条件に合致した場合に少しずつ値が-1.0f～1.0fの間を増減するクラス
	// 最初に条件を設定して後はgetValueで値を受け取るだけ
	class SmoothNormalize final {
	private:
		//====================================================================================================
		// メンバ変数

		float value_ = 0.0f;
		float ips_ = 1.0f;
		bool* positive_ = nullptr;
		bool* negative_ = nullptr;

		//====================================================================================================
	public:
		SmoothNormalize() {}
		~SmoothNormalize() {}

		//====================================================================================================
		// メンバ関数

		// 条件のポインタの設定
		void setCondition(bool* negative, bool* positive);

		// 更新
		// 毎フレーム呼ぶ
		void update();

		// 1秒当たりの増加量の設定
		// IPS = Increase Per Second
		inline void setIPS(const float ips) { ips_ = ips; }

		// 値の取得
		inline float getValue() const { return value_; }

		// 値のリセット
		inline void resetValue() { value_ = 0.0f; }

		//====================================================================================================
	};

}
