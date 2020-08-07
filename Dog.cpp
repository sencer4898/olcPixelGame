#include "Dog.h"
#include "ShootingGame.h"
using namespace std;

Dog::Dog(double xIn, double yIn, double speedIn, double damageIn, double hpmaxIn, double hpcurrentIn, ShootingGame* shootIn) : LivingEntity(xIn, yIn, speedIn, damageIn, hpmaxIn, hpcurrentIn, shootIn)
{
	hpcurrent = 10;
	hpmax = 10;
	speed = 75;
}

void Dog::DrawSprite(ShootingGame* theGame) {
	theGame->DrawSprite(x - 12, y - 12, theGame->dogSprite.getSprite(), 1);
};