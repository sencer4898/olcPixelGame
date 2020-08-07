#include <string>
#include "Sprite.h"

void SpriteClass::SetSprite(string s) {
	sprite = make_shared<olc::Sprite>(s);
}

shared_ptr<olc::Sprite> SpriteClass::getSprite() {
	return sprite;
}


