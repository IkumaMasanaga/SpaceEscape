#pragma once
#include "../library/t2klib.h"


namespace spe {

	class Timer final : public mylib::Singleton<Timer> {
	private:
		// 基底クラスで生成するため
		friend class mylib::Singleton<Timer>;

		Timer() {}

		//====================================================================================================
		// メンバ変数

		// 経過時間
		float time_ = TIME_LIMIT;

		//====================================================================================================
	public:
		~Timer() {}

		//====================================================================================================
		// メンバ定数

		// 制限時間
		inline static const float TIME_LIMIT = 180.0f;

		//====================================================================================================
		// メンバ変数

		// 経過時間（参照用）
		const float& TIME = time_;

		//====================================================================================================
		// メンバ関数

		// 更新
		void update();

		// クリアタイムを取得
		inline float getClearTime() const { return TIME_LIMIT - time_; }

		//====================================================================================================
	};

}
