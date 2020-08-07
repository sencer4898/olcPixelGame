#pragma once
#include "Bonus.h"
using namespace std;

class ShootingGame;

class HealthBonus : public Bonus
{
public:
	HealthBonus(double xIn, double yIn, ShootingGame* shootIn);
	virtual void BonusActive(shared_ptr<Hero> hero, ShootingGame* theGame);
	virtual void DrawSprite(ShootingGame* theGame);
};

