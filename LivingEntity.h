#pragma once
#include "MovingEntity.h"
using namespace std;

class ShootingGame;

	class LivingEntity : public MovingEntity 
	{
	protected:
		double hpmax;
		double hpcurrent;
		void hpUpdate(double a);
	public:
		LivingEntity(double xIn, double yIn, double hpmaxIn, double hpcurrentIn, double speedIn, double damageIn, ShootingGame* shootIn);
		void DrawEntityHpBar(ShootingGame* theGame);
		void getHit(shared_ptr<MovingEntity> projectile);
		bool getHurtIsDead(double a);
	};