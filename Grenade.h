#pragma once
#include "MovingEntity.h"

using namespace std;

class ShootingGame;

class Grenade : public MovingEntity
{
	double destinationX;
	double destinationY;
	double detonationTimeLeft;
	bool ready;
public:
	Grenade(double xIn, double yIn,double destX, double destY,double speedIn, double damageIn, ShootingGame* shootIn);
	void grenadeMove(float fElapsedTime, ShootingGame* theGame);
	virtual void DrawSprite(ShootingGame* theGame);
	bool detonationCountdown(float fElapsedTime);
	bool didReach();
	void updateReady();
};

