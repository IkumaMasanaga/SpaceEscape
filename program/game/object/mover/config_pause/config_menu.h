#pragma once
#include "config_pause_menu_frame.h"


namespace spe {

	class UIFrame;

	class ConfigMenu final : public ConfigPauseMenuFrame {
	public:
		using SharedPtr = std::shared_ptr<ConfigMenu>;
		using WeakPtr = std::weak_ptr<ConfigMenu>;
	private:
		//====================================================================================================
		// �����o�֐�

		// ������
		void onCreatedOfMenuFrame() final override;

		//====================================================================================================
	public:
		ConfigMenu() {}
		~ConfigMenu() {}

		//====================================================================================================
		// �����o�萔

		// �I�����ڒ萔
		inline static const int HOW_TO_PLAY = 0;
		inline static const int ITEM = 1;
		inline static const int ENDING = 2;
		inline static const int RANKING = 3;
		inline static const int VOLUME = 4;
		inline static const int RESET = 5;
		inline static const int BACK = 6;

		//====================================================================================================
	};

}
