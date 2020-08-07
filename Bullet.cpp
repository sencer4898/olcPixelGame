#include "ShootingGame.h"
#include "Bullet.h"
#include <iostream>
#include "olcSimpleEngine.h"
using namespace std;

Bullet ::Bullet(double xIn, double yIn, double dirXIn, double dirYIn, double speedIn, double damageIn, ShootingGame* shootIn) : MovingEntity(xIn, yIn, speedIn, damageIn, shootIn)
{
	dirX = dirXIn;
	dirY = dirYIn;
}

void Bullet::bulletMove(float fElapsedTime) {
	x = x + dirX * speed * fElapsedTime;
	y = y + dirY * speed * fElapsedTime;
}

void Bullet::drawBullet(ShootingGame* theGame) {
	theGame->DrawCircle(x, y, 1, olc::YELLOW);
}

void Bullet::DrawSprite(ShootingGame* theGame) {

}