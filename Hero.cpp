#include "Hero.h"
#include "ShootingGame.h"
#include "olcPGEX_Graphics2D.h"
#define PI 3.14159265359
using namespace std;

class Bullet;
vector<Bullet> bullets;

Hero :: Hero(double xIn, double yIn, double speedIn, double damageIn, double hpmaxIn, double hpcurrentIn,int grenadeStockIn, ShootingGame* shootIn) :LivingEntity(xIn, yIn, speedIn, damageIn, hpmaxIn, hpcurrentIn, shootIn)
{
	hpcurrent = 50;
	hpmax = 100;
	grenadeStock = grenadeStockIn;
	poisonTimer = 0;
	poisonDamage = 0;
}


void Hero::MoveX(float fElapsedTime, int leftright) {
	x = x + fElapsedTime * speed * leftright;
}

void Hero::MoveY(float fElapsedTime, int updown) {
	y = y + fElapsedTime * speed * updown;
}


void Hero::HeroHeal(ShootingGame* theGame) {
	if (hpcurrent < hpmax) {
		theGame->HealthIndicatorIncrease();
	}
	poisonTimerReset();
	healthIncrease();
}

void Hero::healthIncrease() {
	if (hpcurrent + 20 < hpmax) {
		hpcurrent += 20;
	}
	else {
		hpcurrent = hpmax;
	}
}

void Hero::shoot(ShootingGame* theGame) {
	theGame->heroShoot(x, y);
}


void Hero::HeroRotate(olc::GFX2D::Transform2D* t, ShootingGame* theGame) {
	t->Rotate(atan2((theGame->GetMouseX() - x), (theGame->GetMouseY() - y)) - PI / 2);
}

void Hero::HeroTranslate(olc::GFX2D::Transform2D* t) {
	t->Translate(x, y);
}

void Hero::gotHeal(ShootingGame* theGame, float time) {
	theGame->HealthBonusIndicator(x, y, time);
};

void Hero::DivineShield(ShootingGame* theGame) {
	theGame->DivineCounterStart();
}

void Hero::DrawSprite(ShootingGame* theGame) {

}

void Hero::gotGrenade(ShootingGame* theGame, float fElapsedTime) {
	theGame->GrenadeBonusIndicator(x, y, fElapsedTime);
}

void Hero::grenadeIncrease() {
	grenadeStock++;
}

bool Hero::checkGrenade() {
	if (grenadeStock > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void Hero::throwGrenade(ShootingGame* theGame) {
	grenadeStock--;
	theGame->gameThrowGrenade(x, y);
}

void Hero::getPoisoned(double poisonDamageIn) {
	poisonTimerUpdate();
	poisonDamage = poisonDamageIn;
}

void Hero::poisonTimerUpdate() {
	poisonTimer = 30;
}

void Hero::poisonTimerReset() {
	poisonTimer = 0;
}

void Hero::poisonHurts(float fElapsedTime) {
	if (poisonTimer > 0) {
		hpUpdate(fElapsedTime*poisonDamage);
		poisonTimer -= fElapsedTime;
	}
}