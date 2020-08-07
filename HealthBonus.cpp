#include "ShootingGame.h"
#include "HealthBonus.h"
using namespace std;

HealthBonus::HealthBonus(double xIn, double yIn, ShootingGame* shootIn) : Bonus(xIn, yIn, shootIn) {
	
}

void HealthBonus::BonusActive(shared_ptr<Hero> hero, ShootingGame* theGame) {
	hero->HeroHeal(theGame);
}

void HealthBonus::DrawSprite(ShootingGame* theGame) {
	theGame->DrawSprite(x - 12, y - 12, theGame->healthBonusSprite.getSprite(), 1);
};