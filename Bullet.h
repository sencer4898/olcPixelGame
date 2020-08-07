#pragma once
#include "MovingEntity.h"

using namespace std;

class ShootingGame;

class Bullet : public MovingEntity 
{
	double dirX;
	double dirY;
public:
	Bullet(double xIn, double yIn, double dirXIn, double dirYIn, double speedIn, double damageIn, ShootingGame* shootIn);
	void bulletMove(float fElapsedTime);
	void drawBullet(ShootingGame* theGame);
	virtual void DrawSprite(ShootingGame* theGame);
};

