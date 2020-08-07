#include "ShootingGame.h"
#include "Zombie.h"
#include "Hero.h"
#include "Bullet.h"
#include "HealthBonus.h"
#include "ArmorBonus.h"
using namespace std;



Zombie :: Zombie(double xIn, double yIn, double hpmaxIn, double hpcurrentIn, double speedIn, double damageIn,  double attackCDIn, double attackRateIn, double rangeIn, ShootingGame* shootIn) : LivingEntity(xIn, yIn, hpmaxIn, hpcurrentIn, speedIn, damageIn, shootIn)
{
	range = rangeIn;
	attackCD = attackCDIn;
	attackRate = attackRateIn;
}


bool Zombie::attackCounter(float fElapsedTime) {
	attackCD -= fElapsedTime;
	if (attackCD <= 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void Zombie::CdReset() {
	attackCD = attackRate;
}

void Zombie::HealthBonusCreate(ShootingGame* theGame) {
	theGame->HealthCreate(theGame, x, y);
}


void Zombie::ArmorBonusCreate(ShootingGame* theGame) {
	theGame->ArmorCreate(theGame, x, y);
}

void Zombie::GrenadeBonusCreate(ShootingGame* theGame) {
	theGame->GrenadeCreate(theGame, x, y);
}

bool Zombie::isInRange(shared_ptr<Hero> myHero) {
	if (myHero->distanceCalculator(x, y) < range) {
		return 1;
	}
	else {
		return 0;
	}
}

bool Zombie::isGonnaGetHit(shared_ptr<Entity> myEntity) {
	if (myEntity->distanceCalculator(x, y) < range) {
		return 1;
	}
	else {
		return 0;
	}
}