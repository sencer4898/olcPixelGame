#pragma once
#include "Entity.h"
using namespace std;

class ShootingGame;
class Hero;

class Bonus : public Entity
{
public:
	Bonus(double xIn, double yIn, ShootingGame* shootIn);
	double BonusCheck(double heroX, double heroY);
	virtual void BonusActive(shared_ptr<Hero> hero, ShootingGame* theGame)=0;
};
