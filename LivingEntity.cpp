#include "ShootingGame.h"
#include "LivingEntity.h"
#include "olcSimpleEngine.h"

using namespace std;

class ShootingGame;

LivingEntity::LivingEntity(double xIn, double yIn, double hpmaxIn, double hpcurrentIn, double speedIn, double damageIn, ShootingGame* shootIn) :MovingEntity(xIn, yIn, speedIn, damageIn, shootIn)
{
	hpmax = hpmaxIn;
	hpcurrent = hpcurrentIn;
}


bool LivingEntity::getHurtIsDead(double a) {
	hpUpdate(a);
	if (hpcurrent <= 0) { return 1; }
	else { return 0; };
}

void LivingEntity::hpUpdate(double a) {
	hpcurrent -= a;
}

void LivingEntity::DrawEntityHpBar(ShootingGame* theGame) {
	theGame->DrawHPBar(int(x), int(y-20), int(hpmax), int(hpcurrent));
};

void LivingEntity::getHit(shared_ptr<MovingEntity> projectile) {
	hpcurrent = projectile->DamageFunction(hpcurrent);
}