#pragma once
#include "config_pause_menu_frame.h"


namespace spe {

	class UIFrame;

	class PauseMenu final : public ConfigPauseMenuFrame {
	public:
		using SharedPtr = std::shared_ptr<PauseMenu>;
		using WeakPtr = std::weak_ptr<PauseMenu>;
	private:
		//====================================================================================================
		// ƒƒ“ƒoŠÖ”

		// ¶¬
		void onCreatedOfMenuFrame() final override;

		//====================================================================================================
	public:
		PauseMenu() {}
		~PauseMenu() {}

		//====================================================================================================
		// ƒƒ“ƒo’è”

		// ‘I‘ğ€–Ú’è”
		inline static const int BACK = 0;
		inline static const int HOW_TO_PLAY = 1;
		inline static const int ITEM = 2;
		inline static const int VOLUME = 3;
		inline static const int TITLE = 4;

		//====================================================================================================
	};

}
