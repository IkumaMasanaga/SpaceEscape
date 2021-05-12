#include "planet_key_item.h"


namespace spe {

	PlanetKeyItem::SharedPtr PlanetKeyItem::create(const std::string& sprite_path, const PlanetID planet_id, const std::string& text_path) {
		
		PlanetKeyItem::SharedPtr ptr = dxe::CollisionObject::create<PlanetKeyItem>();
		ptr->setName("key_item");
		dxe::Sprite::SharedPtr sprite = dxe::Sprite::createFromFile(sprite_path);
		ptr->pushChild(sprite);

		const float SPRITE_WIDTH = (float)sprite->getTexture()->getWidth();
		const float SPRITE_HEIGHT = (float)sprite->getTexture()->getHeight();
		
		std::vector<std::vector<std::string>> sd = t2k::loadCsv("data/stars.csv");

		const int GENERATE_NUM = 10;
		const t2k::Vector3 LEFT_TOP_LIMIT = t2k::Vector3(-SPRITE_WIDTH * 0.6f, -SPRITE_HEIGHT * 0.6f, 0.0f);
		const t2k::Vector3 RIGHT_BOTTOM_LIMIT = t2k::Vector3(SPRITE_WIDTH * 0.6f, SPRITE_HEIGHT * 0.6f, 0.0f);
		const float ANIMATION_TIME_MIN = 0.5f;
		const float ANIMATION_TIME_MAX = 1.5f;

		for (int i = 0; i < GENERATE_NUM; ++i) {

			// —”‚ÅF‚ðŒˆ’è
			const int C = rand() % sd.size();

			dxe::AnimationSprite::SharedPtr anim = dxe::AnimationSprite::create<dxe::AnimationSprite>();
			anim->registAnimation("star", t2k::Texture::createVectorFromFile(sd[C][1], std::stoi(sd[C][2]), std::stoi(sd[C][3]), std::stoi(sd[C][4]), std::stoi(sd[C][5]), std::stoi(sd[C][6])));
			anim->transform_.position_ = t2k::Vector3(t2k::randomRangeF(LEFT_TOP_LIMIT.x, RIGHT_BOTTOM_LIMIT.x), t2k::randomRangeF(LEFT_TOP_LIMIT.y, RIGHT_BOTTOM_LIMIT.y), 0.0f);
			anim->alpha_ = 0.5f;
			anim->play("star", t2k::randomRangeF(ANIMATION_TIME_MIN, ANIMATION_TIME_MAX), true);
			ptr->pushChild(anim);
		}
		
		dxe::CollisionRect::SharedPtr rect = dxe::CollisionRect::create((int)SPRITE_WIDTH / 2, (int)SPRITE_HEIGHT / 2);
		rect->is_trigger_ = true;
		ptr->addCollisionRect("key_item", rect);
		
		ptr->sprite_file_path_ = sprite_path;
		ptr->text_file_path_ = text_path;
		ptr->planet_id_ = planet_id;

		return ptr;
	}

}
