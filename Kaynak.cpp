#include "olcSimpleEngine.h"
#include "olcPGEX_Graphics2D.h"
#include "vector"
#define PI 3.14159265359
using namespace std;

double distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

class Entity{
protected:
	double x;
	double y;
};
class MovingEntity : public Entity {
protected:
	double speed;
	double damage;
};

class Bullet : public MovingEntity {
	double dirX;
	double dirY;
public:
	Bullet(double xIn, double yIn, double dirXIn, double dirYIn, double speedIn, double damageIn)
	{
		x = xIn;
		y = yIn;
		dirX = dirXIn;
		dirY = dirYIn;
		speed = speedIn;
		damage = damageIn;
	}
};

class LivingEntity : public MovingEntity {
protected:
	double hpmax;
	double hpcurrent;
};

class Zombie : public LivingEntity {
	double attackCD;
	double attackrate;
	double spawnCD;
	double spawnrate;
public:
	Zombie(double xIn, double yIn, double speedIn, double damageIn, double hpIn, double spawnCDIn=0, double spawnrateIn=5,double attackCDIn = 0, double attackrateIn = 2)
	{
		x = xIn;
		y = yIn;
		speed = speedIn;
		damage = damageIn;
		hpmax = hpIn;
		hpcurrent = hpmax;
		spawnCD = spawnCDIn;
		spawnrate = spawnrateIn;
		attackCD = attackCDIn;
		attackrate = attackrateIn;
	}
};

class Hero : public LivingEntity {
	x = ScreenWidth() / 2;
	y = ScreenHeight() / 2;
	heroSpeed = 100;
};

class Bonus : public Entity {
public:
	Bonus(double xIn, double yIn) {
		x = xIn;
		y = yIn;
	}
};

class ShootingGame : public olc::PixelGameEngine {
	int level;
	double gameTime;
	bool gameEnd;

	vector<Bullet> bullets;
	vector<Zombie> zombies;
	vector<Bonus> bonuses;

	shared_ptr<olc::Sprite> bonusSprite;
	shared_ptr<olc::Sprite> manSprite;
	vector<shared_ptr<olc::Sprite>> levelSprites;
	shared_ptr<olc::Sprite> deadSprite;
	shared_ptr<olc::Sprite> zombieSprite;

	void DrawHPBar(int x, int y, int HPMax, int HPCurrent)
	{
		double ratio = (double)(HPCurrent) / (double)HPMax;
		for (int i = x - 5; i < 5 + x; ++i)
			if (i < x - 5 + ratio * 10)
				DrawRect(i, y + 14, 1, 1, olc::GREEN);
			else
				DrawRect(i, y + 14, 1, 1, olc::RED);
	}

public:

	bool OnUserCreate() override //override
	{
		manSprite = make_shared<olc::Sprite>("Sprites/ManTrans.png");
		deadSprite = make_shared<olc::Sprite>("Sprites/Dead.png");
		zombieSprite = make_shared<olc::Sprite>("Sprites/zombie.png");
		bonusSprite = make_shared<olc::Sprite>("Sprites/firstaid.png");

		x = ScreenWidth() / 2;
		y = ScreenHeight() / 2;
		heroSpeed = 100;

		spawnRate = 5;
		spawnCD = 0;

		hpmax = 100;
		hpcurr = 50;

		gameTime = 0;
		gameEnd = false;

		for (int i = 0; i < 7; ++i)
			levelSprites.push_back(make_shared<olc::Sprite>("Sprites/Level" + to_string(i + 1) + ".png"));

		srand(NULL);
		return true;
	}
};