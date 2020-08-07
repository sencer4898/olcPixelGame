#include "ShootingGame.h"
#include "Grenade.h"
#include "olcSimpleEngine.h"
using namespace std;

Grenade::Grenade(double xIn, double yIn, double destX, double destY, double speedIn, double damageIn, ShootingGame* shootIn) : MovingEntity(xIn, yIn, speedIn, damageIn, shootIn)
{
	destinationX = destX;
	destinationY = destY;
	detonationTimeLeft = 1;
	ready = 0;
}

void Grenade::grenadeMove(float fElapsedTime, ShootingGame* theGame) {
	double dirX = destinationX - x;
	double dirY = destinationY - y;
	double dist = sqrt((dirX * dirX) + (dirY * dirY));
	if(x!=destinationX){
	x = x + (dirX/dist) * speed * fElapsedTime;
	y = y + (dirY/dist) * speed * fElapsedTime;	
	}
	
	if (theGame->distance(x, y, destinationX, destinationY)<5) {
		updateReady();
	}
}

void Grenade::DrawSprite(ShootingGame* theGame) {
	theGame->DrawSprite(x - 12, y - 12, theGame->grenadeBonusSprite.getSprite(), 1);
}

bool Grenade::detonationCountdown(float fElapsedTime) {
	detonationTimeLeft -= fElapsedTime;
	if (detonationTimeLeft <= 0) {
		return 1;
	}
	else {
		return 0;
	}
}

bool Grenade::didReach() {
	if (ready) {
		return 1;
	}
	else {
		return 0;
	}
}

void Grenade::updateReady() {
	ready = 1;
}