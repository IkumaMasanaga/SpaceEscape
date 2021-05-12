#include "planet_enemy.h"


namespace spe {

	void PlanetEnemy::onCreated() {
		setName("enemy");
		animation_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		// —”‚ÅŒü‚«‚ğ•Ï‚¦‚é
		animation_->is_flip_y_ = ((rand() % 2) == 0);
		pushChild(animation_);
		// ”h¶æ‚Ì¶¬ŠÖ”ŒÄ‚Ño‚µ
		onCreatedOfEnemy();
	}

}
