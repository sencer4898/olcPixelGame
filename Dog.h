#pragma once
#include "LivingEntity.h"
using namespace std;

class Dog : public LivingEntity
{
	
public:
	Dog(double xIn, double yIn, double speedIn, double damageIn, double hpmaxIn, double hpcurrentIn, ShootingGame* shootIn);
	virtual void DrawSprite(ShootingGame* theGame);
};