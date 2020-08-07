#pragma once
#include "olcSimpleEngine.h"
#include "olcPGEX_Graphics2D.h"

using namespace std;

class SpriteClass {
	shared_ptr<olc::Sprite> sprite;
public:
	void SetSprite(string s);
	shared_ptr<olc::Sprite> getSprite();
};