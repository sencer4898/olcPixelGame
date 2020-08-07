#pragma once
#include "Entity.h"
using namespace std;

class ShootingGame;

class MovingEntity : public Entity
{
protected:
	double speed;
	double damage;
public:
	MovingEntity(double xIn, double yIn, double speedIn, double damageIn, ShootingGame* shootIn);
	bool IsOutWindow(int a, int b);
	void DirectedMove(float fElapsedTime, shared_ptr<Entity> target, double proximity);
	double DamageFunction(double a);
};