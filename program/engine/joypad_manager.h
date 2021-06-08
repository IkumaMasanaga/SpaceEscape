#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class JoypadManager final : public mylib::Singleton<JoypadManager> {
	private:
		// 基底クラスで生成するため
		friend class mylib::Singleton<JoypadManager>;

		JoypadManager() {}

		//====================================================================================================
		// メンバ変数

		mylib::JoypadXInput::SharedPtr joypad_ = nullptr;

		//====================================================================================================
	public:
		~JoypadManager() {}

		//====================================================================================================
		// メンバ関数

		// 更新
		void update();

		// ジョイパッドの取得
		inline mylib::JoypadXInput::SharedPtr getJoypad() const { return joypad_; }

		//====================================================================================================
	};

}
