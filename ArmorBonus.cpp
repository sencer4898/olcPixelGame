#include "ShootingGame.h"
#include "ArmorBonus.h"
using namespace std;

ArmorBonus::ArmorBonus(double xIn, double yIn, ShootingGame* shootIn) : Bonus(xIn, yIn,shootIn) {

}

void ArmorBonus::BonusActive(shared_ptr<Hero> hero, ShootingGame* theGame) {
	hero->DivineShield(theGame);
}

void ArmorBonus::DrawSprite(ShootingGame* theGame) {
	theGame->DrawSprite(x - 12, y - 12, theGame->armorBonusSprite.getSprite(), 1);
};