#pragma once
#include "Bonus.h"
using namespace std;

class ShootingGame;

class GrenadeBonus : public Bonus
{
public:
	GrenadeBonus(double xIn, double yIn, ShootingGame* shootIn);
	virtual void BonusActive(shared_ptr<Hero> hero, ShootingGame* theGame);
	virtual void DrawSprite(ShootingGame* theGame);
};

