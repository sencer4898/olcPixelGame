#pragma once
#include "Zombie.h"

using namespace std;

class ZombieToxic : public Zombie {

public:
	ZombieToxic(double xIn, double yIn, double hpmaxIn, double hpcurrentIn, double speedIn, double damageIn, double attackCDIn, double attackRateIn, double rangeIn, ShootingGame* shootIn);
	virtual void DrawSprite(ShootingGame* theGame);
	virtual void attackHero(shared_ptr<Hero> myHero);

};