#include "debug_command.h"

#include "../scene/logo.h"
#include "../scene/title.h"
#include "../scene/config.h"
#include "../scene/prologue.h"
#include "../scene/space.h"
#include "../scene/planet.h"
#include "../scene/epilogue.h"
#include "../scene/demo_movie.h"

#include "../player_status.h"
#include "../save_data.h"


void DebugCommand::onCreated() {
	is_update_always_ = true;
	update_priority_ = -FLT_MAX;
	setName("DebugCommand");
	mylib::Debug::clearLog();
	mylib::Debug::log("DebugCommand ON");
}

void DebugCommand::update() {

	dxe::DxEngine& engine = dxe::DxEngine::getInstance();
	spe::PlayerStatus& status = spe::PlayerStatus::getInstance();

	// 各シーン切り替え
	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_LCONTROL)) {

		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_L)) {
			engine.changeScene(dxe::Scene::create<spe::Logo>());
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_T)) {
			engine.changeScene(dxe::Scene::create<spe::Title>());
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C)) {
			engine.changeScene(dxe::Scene::create<spe::Config>());
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_P)) {
			engine.changeScene(dxe::Scene::create<spe::Prologue>());
		}

		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_Q)) {
			engine.changeScene(spe::Epilogue::create(spe::EndType::GOOD_NEW_WORLD));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_W)) {
			engine.changeScene(spe::Epilogue::create(spe::EndType::GOOD_SURVIVAL));
		}

		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_M)) {
			engine.changeScene(dxe::Scene::create<spe::DemoMovie>());
		}

		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_S)) {
			engine.changeScene(dxe::Scene::create<spe::Space>());
		}

		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_0)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/00_sun/a"));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_1)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/01_mercury/a"));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_2)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/02_venus/a"));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_3)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/03_earth/a"));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_4)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/04_mars/a"));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_5)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/05_jupiter/a"));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_6)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/06_saturn/a"));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_7)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/07_uranus/a"));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_8)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/08_neptune/a"));
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_9)) {
			engine.changeScene(spe::Planet::create("space_to_planet", "data/scene/planet/09_pluto/a"));
		}

	}

	if (t2k::Input::isKeyDown(t2k::Input::KEYBORD_LSHIFT)) {

		// アイテム獲得
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_0)) {
			status.getItem(spe::PlanetID::SUN);
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_1)) {
			status.getItem(spe::PlanetID::MERCURY);
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_2)) {
			status.getItem(spe::PlanetID::VENUS);
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_3)) {
			status.getItem(spe::PlanetID::EARTH);
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_4)) {
			status.getItem(spe::PlanetID::MARS);
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_5)) {
			status.getItem(spe::PlanetID::JUPITER);
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_6)) {
			status.getItem(spe::PlanetID::SATURN);
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_7)) {
			status.getItem(spe::PlanetID::URANUS);
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_8)) {
			status.getItem(spe::PlanetID::NEPTUNE);
		}
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_9)) {
			status.getItem(spe::PlanetID::PLUTO);
		}

		// エネルギー最大
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_E)) {
			status.changeEnergy(spe::PlayerStatus::MAX_ENERGY);
		}

		// ステータスリセット
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_R)) {
			spe::PlayerStatus::destroy();
		}

		// ログのクリア
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_C)) {
			mylib::Debug::clearLog();
		}

		// 衝突判定矩形描画切り替え
		if (t2k::Input::isKeyDownTrigger(t2k::Input::KEYBORD_H)) {
			dxe::CollisionManager::getInstance().is_render_debug_area_ ^= true;
		}

	}

}
