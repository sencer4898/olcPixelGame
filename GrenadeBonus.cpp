#include "ShootingGame.h"
#include "GrenadeBonus.h"
using namespace std;

GrenadeBonus::GrenadeBonus(double xIn, double yIn,ShootingGame* shootIn) : Bonus(xIn, yIn, shootIn) {

}

void GrenadeBonus::BonusActive(shared_ptr<Hero> hero, ShootingGame* theGame) {
	hero->grenadeIncrease();
	theGame->GrenadeIndicatorIncrease();
}

void GrenadeBonus::DrawSprite(ShootingGame* theGame) {
	theGame->DrawSprite(x - 12, y - 12, theGame->grenadeBonusSprite.getSprite(), 1);
};