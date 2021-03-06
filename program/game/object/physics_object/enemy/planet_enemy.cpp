#include "planet_enemy.h"


namespace spe {

	void PlanetEnemy::onCreated() {
		setName("enemy");
		animation_ = dxe::AnimationSprite::create<dxe::AnimationSprite>();
		// 乱数で向きを変える
		animation_->is_flip_y_ = ((rand() % 2) == 0);
		pushChild(animation_);
		// 派生先の生成時関数呼び出し
		onCreatedOfEnemy();
	}

}
