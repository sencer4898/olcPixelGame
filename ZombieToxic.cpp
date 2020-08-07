#include "ShootingGame.h"
#include "ZombieToxic.h"
#include "Hero.h"
#include "HealthBonus.h"
#include "ArmorBonus.h"
using namespace std;

ZombieToxic::ZombieToxic(double xIn, double yIn, double hpmaxIn, double hpcurrentIn, double speedIn, double damageIn, double attackCDIn, double attackRateIn, double rangeIn, ShootingGame* shootIn) :Zombie(xIn, yIn, hpmaxIn, hpcurrentIn, speedIn, damageIn, attackCDIn, attackRateIn, rangeIn, shootIn) {

}


void ZombieToxic::DrawSprite(ShootingGame* theGame) {
	theGame->DrawSprite(x - 12, y - 12, theGame->zombieToxicSprite.getSprite(), 1);
}

void ZombieToxic::attackHero(shared_ptr<Hero> myHero) {
	myHero->getPoisoned(damage);
};
