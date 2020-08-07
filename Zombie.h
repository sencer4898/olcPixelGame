#pragma once
#include "LivingEntity.h"
#include "ShootingGame.h"

using namespace std;

class Bullet;
class Hero;
class Bonus;
class ShootingGame;

class Zombie : public LivingEntity 
{
	double attackCD;
	double attackRate;
	double range;
public:
	Zombie(double xIn, double yIn, double hpmaxIn, double hpcurrentIn, double speedIn, double damageIn, double attackCDIn, double attackRateIn, double rangeIn, ShootingGame* shootIn);
	bool attackCounter(float fElapsedTime);
	void CdReset();
	void HealthBonusCreate(ShootingGame* theGame);
	void ArmorBonusCreate(ShootingGame* theGame);
	void GrenadeBonusCreate(ShootingGame* theGame);
	virtual void attackHero(shared_ptr<Hero> myHero) = 0;
	virtual void DrawSprite(ShootingGame* theGame)=0;
	bool isInRange(shared_ptr<Hero> myHero);
	bool isGonnaGetHit(shared_ptr<Entity> myEntity);
};
