#include "ShootingGame.h"
#include "MovingEntity.h"
#include <iostream>

using namespace std;

MovingEntity::MovingEntity(double xIn, double yIn, double speedIn, double damageIn, ShootingGame* shootIn) : Entity(xIn, yIn, shootIn) {
	speed = speedIn;
	damage = damageIn;
}


bool MovingEntity::IsOutWindow(int a, int b) {
	int isOut = 0;
	if (y <= 0) { y = 0; isOut++; }
	if (x <= 0) { x = 0; isOut++; }
	if (y >= a) { y = a; isOut++; }
	if (x >= b) { x = b; isOut++; }
	return isOut;
}


void MovingEntity::DirectedMove(float fElapsedTime, shared_ptr<Entity> target, double proximity) {
	double dirX = target->directionFinderX(x);
	double dirY = target->directionFinderY(y);
	double dist = sqrt((dirX * dirX) + (dirY * dirY));
	if(distance(target)>proximity){
	x = x + (dirX / dist) * speed * fElapsedTime;
	y = y + (dirY / dist) * speed * fElapsedTime;
	}
}

double MovingEntity::DamageFunction(double a) {
	return a - damage;
}