#pragma once
#include "Bonus.h"
using namespace std;

class ShootingGame;

class ArmorBonus : public Bonus
{
public:
	ArmorBonus(double xIn, double yIn, ShootingGame* shootIn);
	virtual void BonusActive(shared_ptr<Hero> hero, ShootingGame* theGame);
	virtual void DrawSprite(ShootingGame* theGame);
};

