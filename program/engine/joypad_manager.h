#pragma once
#include "../library/t2klib.h"


namespace dxe {

	class JoypadManager final : public t2k::Singleton<JoypadManager> {
	private:
		// 基底クラスで生成するため
		friend class t2k::Singleton<JoypadManager>;

		JoypadManager() {}

		//====================================================================================================
		// メンバ変数

		t2k::JoypadXInput::SharedPtr joypad_ = nullptr;

		//====================================================================================================
	public:
		~JoypadManager() {}

		//====================================================================================================
		// メンバ関数

		// 更新
		void update();

		// ジョイパッドの取得
		inline t2k::JoypadXInput::SharedPtr getJoypad() const { return joypad_; }

		//====================================================================================================
	};

}
