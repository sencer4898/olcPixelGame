#pragma once
#include "Zombie.h"

using namespace std;

class ZombieBig : public Zombie {

public:
	ZombieBig(double xIn, double yIn, double hpmaxIn, double hpcurrentIn, double speedIn, double damageIn, double attackCDIn, double attackRateIn, double rangeIn, ShootingGame* shootIn);
	virtual void DrawSprite(ShootingGame* theGame);
	virtual void attackHero(shared_ptr<Hero> myHero);

};