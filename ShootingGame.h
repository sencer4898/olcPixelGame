#pragma once
#include "olcSimpleEngine.h"
#include "olcPGEX_Graphics2D.h"
#include "Zombie.h"
#include "Hero.h"
#include "Bullet.h"
#include "Dog.h"
#include "HealthBonus.h"
#include "ArmorBonus.h"
#include "GrenadeBonus.h"
#include "Sprite.h"
#include "Grenade.h"
#include <vector>
#define PI 3.14159265359

using namespace std;

class Zombie;
class Hero;
class Bonus;
class Bullet;
class SpriteClass;
class Dog;
class Grenade;

class ShootingGame : public olc::PixelGameEngine {
	int level;
	double gameTime;
	bool gameEnd;
	double spawnCD;
	double spawnRate;
	double DivineCounter;
	double HealthIndicator;
	double GrenadeIndicator;

	vector<shared_ptr<Bonus>> bonuses;
	vector<shared_ptr<Zombie>> enemies;
	vector<shared_ptr<Bullet>> bullets;
	vector<shared_ptr<Hero>> heros;
	vector<shared_ptr<Dog>> dogs;
	vector<shared_ptr<Grenade>> grenades;

	void FrenzySpawnRate();
	void NormalSpawnRate();
	void ChangeLevel();
	void spawnCdReset();
	void DivineCounterCountDown(float fElapsedTime);
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);
	void ChangeGameTime(float fElapsedTime);
	void spawnCdDecraser(float fElapsedTime);
public:

	SpriteClass healthBonusSprite;
	SpriteClass manSprite;
	vector<shared_ptr<olc::Sprite>> levelSprites;
	SpriteClass deadSprite;
	SpriteClass zombieNormalSprite;
	SpriteClass zombieToxicSprite;
	SpriteClass zombieBigSprite;
	SpriteClass dogSprite;
	SpriteClass armorBonusSprite;
	SpriteClass grenadeBonusSprite;

	void DrawHPBar(int x, int y, int HPMax, int HPCurrent);	
	void heroShoot(double x, double y);
	void HealthBonusIndicator(double x, double y, float fElapsedTime);
	void GrenadeBonusIndicator(double x, double y, float fElapsedTime);
	void HealthIndicatorIncrease();
	void GrenadeIndicatorIncrease();
	void DivineCounterStart();
	void HealthCreate(ShootingGame* theGame, double x, double y);
	void ArmorCreate(ShootingGame* theGame, double x, double y);
	void GrenadeCreate(ShootingGame* theGame, double x, double y);
	void gameThrowGrenade(double x, double y);
	double distance(double x1, double y1, double x2, double y2);
};

