#include "ShootingGame.h"
#include "ZombieBig.h"
#include "Hero.h"
#include "HealthBonus.h"
#include "ArmorBonus.h"
using namespace std;

ZombieBig::ZombieBig(double xIn, double yIn, double hpmaxIn, double hpcurrentIn, double speedIn, double damageIn, double attackCDIn, double attackRateIn, double rangeIn, ShootingGame* shootIn) :Zombie(xIn, yIn, hpmaxIn, hpcurrentIn, speedIn, damageIn, attackCDIn, attackRateIn, rangeIn, shootIn) {

}

void ZombieBig::DrawSprite(ShootingGame* theGame) {
	theGame->DrawSprite(x - 12, y - 12, theGame->zombieBigSprite.getSprite(), 1);
}

void ZombieBig::attackHero(shared_ptr<Hero> myHero) {
	myHero->getHurtIsDead(damage);
};
