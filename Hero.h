#pragma once
#include "LivingEntity.h"
#include "olcPGEX_Graphics2D.h"

using namespace std;

class ShootingGame;
class olc::GFX2D::Transform2D;

class Hero : public LivingEntity 
{
	int grenadeStock;
	double poisonTimer;
	double poisonDamage;
	void healthIncrease();
	void poisonTimerUpdate();
	void poisonTimerReset();
public:
	Hero(double xIn, double yIn, double speedIn, double damageIn, double hpmaxIn, double hpcurrentIn, int grenadeStockIn, ShootingGame* shootIn);
	void MoveX(float fElapsedTime, int leftright);
	void MoveY(float fElapsedTime, int updown);
	void HeroHeal(ShootingGame* theGame);
	void shoot(ShootingGame* theGame);
	void HeroRotate(olc::GFX2D::Transform2D* t, ShootingGame* theGame);
	void HeroTranslate(olc::GFX2D::Transform2D* t);
	void gotHeal(ShootingGame* theGame, float time);
	void DivineShield(ShootingGame* theGame);
	virtual void DrawSprite(ShootingGame* theGame);
	void gotGrenade(ShootingGame* theGame, float fElapsedTime);
	bool checkGrenade();
	void throwGrenade(ShootingGame* theGame);
	void grenadeIncrease();
	void getPoisoned(double damage);
	void poisonHurts(float fElapsedTime);
};	