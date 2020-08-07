#include "ShootingGame.h"
#include "Entity.h"
#include "MovingEntity.h"
#include "Dog.h"
#include "Bullet.h"
#include "LivingEntity.h"
#include "Zombie.h"
#include "ZombieBig.h"
#include "ZombieToxic.h"
#include "ZombieNormal.h"
#include "Hero.h"
#include "Sprite.h"
#include <algorithm>
#include <vector>
#include <chrono>
#include <string>
#define PI 3.14159265359

using namespace std;


double ShootingGame::distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void ShootingGame::DrawHPBar(int x, int y, int HPMax, int HPCurrent)
{
	double ratio = (double)(HPCurrent) / (double)HPMax;
	for (int i = x - 5; i < 5 + x; ++i)
		if (i < double(x) - 5 + ratio * 10)
			DrawRect(i, y + 14, 1, 1, olc::GREEN);
		else
			DrawRect(i, y + 14, 1, 1, olc::RED);
}

void ShootingGame::ChangeLevel() 
{
	level = int(gameTime / 10) % 7 + 1;
};

void ShootingGame::ChangeGameTime(float fElapsedTime) 
{
	gameTime += fElapsedTime;
};

void ShootingGame::spawnCdDecraser(float fElapsedTime) {
	spawnCD -= fElapsedTime;
}

void ShootingGame::spawnCdReset() {
	spawnCD += spawnRate;
}

void ShootingGame::heroShoot(double x, double y) {
	double dirX = GetMouseX()-x;
	double dirY = GetMouseY()-y;
	double dist = sqrt((dirX * dirX) + (dirY * dirY));
	bullets.push_back(make_shared<Bullet>(x, y, dirX / dist, dirY / dist, 200, 1, this));
}

void ShootingGame::gameThrowGrenade(double x, double y) {
	grenades.push_back(make_shared<Grenade>(x, y,GetMouseX(), GetMouseY(),200, 10, this));
}

void ShootingGame::HealthCreate(ShootingGame* theGame, double x, double y) {
	bonuses.push_back(make_shared<HealthBonus>(x, y, theGame));
}

void ShootingGame::ArmorCreate(ShootingGame* theGame, double x, double y) {
	bonuses.push_back(make_shared<ArmorBonus>(x, y, theGame));
}

void ShootingGame::GrenadeCreate(ShootingGame* theGame, double x, double y) {
	bonuses.push_back(make_shared<GrenadeBonus>(x, y, theGame));
}

void ShootingGame::DivineCounterCountDown(float fElapsedTime) {
	if (DivineCounter > 0) {
		DivineCounter -= fElapsedTime;
		DrawString(ScreenWidth() / 2 - 60, ScreenHeight() / 2 - 100, "Invincible For: "+to_string(int(DivineCounter)), olc::MAGENTA);
		
	}
	else {
		DivineCounter = 0;
	}
}

void ShootingGame::HealthBonusIndicator(double x, double y, float fElapsedTime) {
	DrawString(x-35, y-35, "HEALTH +20", olc::GREEN, 1);
	HealthIndicator -= fElapsedTime;

}

void ShootingGame::GrenadeBonusIndicator(double x, double y, float fElapsedTime) {
	DrawString(x - 35, y - 35, "GRENADE +1", olc::GREY , 1);
	GrenadeIndicator -= fElapsedTime;

}

void ShootingGame::HealthIndicatorIncrease() {
	HealthIndicator = 2;
	GrenadeIndicator = 0;
}

void ShootingGame::GrenadeIndicatorIncrease() {
	GrenadeIndicator = 2;
	HealthIndicator = 0;
}

void ShootingGame::FrenzySpawnRate() {
	spawnRate = 0.3;
}

void ShootingGame::NormalSpawnRate() {
	spawnRate = 3;
}

void ShootingGame::DivineCounterStart() {
	DivineCounter = 5;
}

bool ShootingGame::OnUserCreate(){
	manSprite.SetSprite("Sprites/ManTrans.png");
	deadSprite.SetSprite("Sprites/Dead.png");
	zombieNormalSprite.SetSprite("Sprites/zombie.png");
	zombieToxicSprite.SetSprite("Sprites/toxicZombie.png");
	zombieBigSprite.SetSprite("Sprites/bigZombie.png");
	healthBonusSprite.SetSprite("Sprites/firstaid.png");
	dogSprite.SetSprite("Sprites/dog.png");
	armorBonusSprite.SetSprite("Sprites/armor.png");
	grenadeBonusSprite.SetSprite("Sprites/bomb20.png");

	gameTime = 0;
	gameEnd = false;
	spawnRate = 5;
	spawnCD = 0;
	DivineCounter = 0;
	HealthIndicator = 0;
	GrenadeIndicator = 0;

	for (int i = 0; i < 7; ++i)
		levelSprites.push_back(make_shared<olc::Sprite>("Sprites/Level" + to_string(i + 1) + ".png"));

	heros.push_back(make_shared<Hero>(ScreenWidth() / 2, ScreenHeight() / 2, 80, 0, 100, 50, 0, this));
	dogs.push_back(make_shared<Dog>(ScreenWidth() / 2, ScreenHeight() / 2, 50, 10, 10, 10, this));

	srand(NULL);
	return true;

}

bool ShootingGame::OnUserUpdate(float fElapsedTime) {

	if (gameEnd) {
		DrawSprite(0, 0, deadSprite.getSprite(), 1);
		DrawString(ScreenWidth() / 2 - 38, ScreenHeight() / 2 - 10, "GAME OVER", olc::DARK_RED);
		DrawString(ScreenWidth() / 2 - 38, ScreenHeight() / 2, "Try again?", olc::BLACK);
		DrawString(ScreenWidth() / 2 - 35, ScreenHeight() / 2 + 10, "Press Y", olc::BLACK);
		DrawString(ScreenWidth() / 2 - 55, ScreenHeight() / 2 + 20, "Press N to exit", olc::BLACK);


		if (GetKey(olc::Y).bPressed)
		{
			OnUserCreate();
		}

		if (GetKey(olc::Key::N).bPressed)
			return false;

		return true;
	}

	ChangeGameTime(fElapsedTime);
	ChangeLevel();

	//ZOMBIE SPAWNS
	if (level == 3) {
		FrenzySpawnRate();
	}
	else {
		NormalSpawnRate();
	}

	spawnCdDecraser(fElapsedTime);
	if (spawnCD <= 0)
	{
		double degree = rand() * 360;
		if(rand() % 5 < 3){
		enemies.push_back(make_shared<ZombieNormal>((cos(degree) * ScreenWidth()) + (ScreenWidth() / 2), (sin(degree) * ScreenHeight()) + (ScreenHeight() / 2), 15, 15, 50, 10, 0, 2, 15, this));
		}
		else if (rand() % 5 < 3) {
		enemies.push_back(make_shared<ZombieToxic>((cos(degree) * ScreenWidth()) + (ScreenWidth() / 2), (sin(degree) * ScreenHeight()) + (ScreenHeight() / 2), 10, 10, 75, 3, 0, 2, 10, this));
		}
		else {
			enemies.push_back(make_shared<ZombieBig>((cos(degree) * ScreenWidth()) + (ScreenWidth() / 2), (sin(degree) * ScreenHeight()) + (ScreenHeight() / 2), 25, 25, 25, 50, 0, 2, 25, this));
		}
		spawnCdReset();
	}

	//ZOMBIE SPAWNS

	//DOG TOGGLE

	if (GetKey(olc::P).bPressed)
	{
		if (dogs.size()<=0) {
			dogs.push_back(make_shared<Dog>(ScreenWidth() / 2, ScreenHeight() / 2, 50, 10, 10, 10, this));
		}
		else {
			dogs.erase(dogs.begin());
		}
	}

	//DOG TOGGLE

	 //SHOOTING
	//NORMAL
	if (GetKey(olc::SPACE).bPressed)
	{
		for (int i = 0; i < heros.size(); ++i)
		{
			heros[i]->shoot(this);
		}
	}
	//NORMAL
	//MACHINE GUN
	if (GetKey(olc::SPACE).bHeld && (level==3||level==4))
	{
		for (int i = 0; i < heros.size(); ++i)
		{
			heros[i]->shoot(this);
		}
	}
	//MACHINE GUN
	//SHOOTING

	//BOMB THROW

	if (GetKey(olc::B).bReleased) {
		for (int i = 0; i < heros.size(); i++) {
			if (heros[i]->checkGrenade()) {
				heros[i]->throwGrenade(this);
			}
		}
	}

	//BOMB THROW

	//UPDATE VARIABLES
	if (GetKey(olc::W).bHeld) 
	{
		for (int i = 0; i < heros.size(); ++i)
		{
			heros[i]->MoveY(fElapsedTime, -1);
		}
	}
	if (GetKey(olc::S).bHeld)
	{
		for (int i = 0; i < heros.size(); ++i)
		{
			heros[i]->MoveY(fElapsedTime, 1);
		}
	}
	if (GetKey(olc::D).bHeld) 
	{
		for (int i = 0; i < heros.size(); ++i)
		{
			heros[i]->MoveX(fElapsedTime, 1);
		}
	}
	if (GetKey(olc::A).bHeld) 
	{
		for (int i = 0; i < heros.size(); ++i)
		{
			heros[i]->MoveX(fElapsedTime, -1);
		}
	}
	//UPDATE VARIABLES

	//KEEP HERO IN WINDOW
	for (int i = 0; i < heros.size(); ++i)
	{
		heros[i]->IsOutWindow(ScreenHeight() - 1, ScreenWidth() - 1);
	}
	//KEEP HERO IN WINDOW

	//BULLETSMOVE
	for (int i = 0; i < bullets.size(); ++i)
	{
		bullets[i]->bulletMove(fElapsedTime);
		if (bullets[i]->IsOutWindow(ScreenHeight() -1, ScreenWidth()-1))
		{
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
	//BULLETSMOVE

	//GRENADES MOVE

	for (int i = 0; i < grenades.size(); i++) {
		grenades[i]->grenadeMove(fElapsedTime, this);
	}

	//GRENADES MOVE

	//BULLETSHIT
	for (int i = 0; i < bullets.size(); ++i)
	{
		for (int j = 0; j < enemies.size(); ++j)
		{
			if (enemies[j]->isGonnaGetHit(bullets[i]))
			{
				enemies[j]->getHit(bullets[i]);
				bullets.erase(bullets.begin() + i);
				i--;
				if (enemies[j]->getHurtIsDead(0))
				{
					//RANDOM BONUS CREATION

					if (rand() % 5 < 2) {
						if (rand() % 5 < 3){
							enemies[j]->HealthBonusCreate(this);
					}
					else {
							enemies[j]->GrenadeBonusCreate(this);
						}
					}
					//RANDOM BONUS CREATION

					enemies.erase(enemies.begin() + j);
					j--;
				}
				break;
			}
		}
	}
	//BULLETSHIT

	//BOMB EXPLODE

	for (int i = 0; i < grenades.size(); ++i)
	{
		if(grenades[i]->didReach())
		{
			if (grenades[i]->detonationCountdown(fElapsedTime)){
		for (int j = 0; j < enemies.size(); ++j)
		{		
				if (grenades[i]->distance(enemies[j]) < 40) {
					enemies[j]->getHit(grenades[i]);
				}			
				if (enemies[j]->getHurtIsDead(0))
				{
					//RANDOM BONUS CREATION

					if (rand() % 5 < 2) {
						if (rand() % 5 < 1) {
							enemies[j]->HealthBonusCreate(this);
						}
						else{
							enemies[j]->ArmorBonusCreate(this);
						}
					}
					//RANDOM BONUS CREATION

					enemies.erase(enemies.begin() + j);
					j--;
				}
		}
		for (int j = 0; j < heros.size(); ++j)
		{
			
			{
				if (grenades[i]->distance(heros[j]) < 40) {
					heros[j]->getHit(grenades[i]);
				}
			}
		}

		grenades.erase(grenades.begin() + i);
		i--;
		break;
			}
		}
	}

	//BOMB EXPLODE

	//HERO BONUS PICK UP
	for (int j = 0; j < heros.size(); ++j)
	{
		for (int i = 0; i < bonuses.size(); i++)
		{
			if (heros[j]->distance(bonuses[i]) <= 10)
			{

				bonuses[i]->BonusActive(heros[j], this);
				

				bonuses.erase(bonuses.begin() + i);
				i--;

			}

		}
	}

	//HERO BONUS PICK UP

	//DOG BONUS PICK UP

	for (int j = 0; j < dogs.size(); ++j)
	{
		for (int i = 0; i < bonuses.size(); i++)
		{
			if (dogs[j]->distance(bonuses[i]) <= 10)
			{

				bonuses[i]->BonusActive(heros[j], this);


				bonuses.erase(bonuses.begin() + i);
				i--;

			}

		}
	}
	
	//DOG BONUS PICK UP

	//BONUS PICK UP

	//ENEMIESMOVE
	for (int j = 0; j < heros.size(); ++j)
	{
		for (int i = 0; i < enemies.size(); ++i)
		{
			
			enemies[i]->DirectedMove(fElapsedTime, heros[j], 0);
			if (enemies[i]->getHurtIsDead(0))
			{
				enemies.erase(enemies.begin() + i);
				i--;
			}
		}
	}
	//ENEMIESMOVE

	//DOGMOVE

	if (bonuses.size()>0) {
		for (int i = 0; i < dogs.size(); i++) {
			dogs[i]->DirectedMove(fElapsedTime, bonuses[0], 0);
		}
	}
	else {
		for (int j = 0; j < heros.size(); ++j) {
			for (int i = 0; i < dogs.size(); i++) {
				dogs[i]->DirectedMove(fElapsedTime, heros[j], 30);
			}
		}
	}
	//DOGMOVE

	//ENEMIESATTACK

	
	for (int j = 0; j < heros.size(); ++j)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->attackCounter(fElapsedTime);

			if((enemies[i]->isInRange(heros[j]))&& (enemies[i]->attackCounter(fElapsedTime)))
			{
				if (DivineCounter<=0) {
					enemies[i]->attackHero(heros[j]);
				}
				enemies[i]->CdReset();
			}
		}
	}

	for (int i = 0; i < heros.size(); i++) {
		heros[i]->poisonHurts(fElapsedTime);
	}


	//ENEMIESATTACK

	//CHECKGAMEOVER


	// If HP is less than 0 or if you press E end game
	for (int j = 0; j < heros.size(); ++j)
	{
		if (heros[j]->getHurtIsDead(0) || GetKey(olc::E).bReleased)
		{

			for (int i = 0; i < enemies.size(); i++)
			{
				enemies.erase(enemies.begin());
				i--;
			}

			for (int i = 0; i < bullets.size(); i++)
			{
				bullets.erase(bullets.begin());
				i--;
			}


			for (int i = 0; i < bonuses.size(); i++)
			{
				bonuses.erase(bonuses.begin());
				i--;
			}

			for (int i = 0; i < heros.size(); i++)
			{
				heros.erase(heros.begin());
				i--;
			}

			for (int i = 0; i < dogs.size(); i++)
			{
				dogs.erase(dogs.begin());
				i--;
			}

			for (int i = 0; i < grenades.size(); i++) 
			{
				grenades.erase(grenades.begin());
				i--;
			}

			gameEnd = true;


		}
	}
	


	//TO BE IMPLEMENTED
//CHECKGAMEOVER

	//DRAWING

	//THE LEVEL
	Clear(olc::BLACK);
	DrawSprite(0, 0, levelSprites[level - 1], 1);
	if (level == 3 || level == 4) {
		DrawString(ScreenWidth() / 2 - 38, ScreenHeight() / 2 - 10, "FRENZYYY!!", olc::YELLOW);
	}

	//THE ARMOR COUNTER
	DivineCounterCountDown(fElapsedTime);
	//

	//HEAL
	if (HealthIndicator>0) {
		for (int i = 0; i < heros.size(); i++) {
			heros[i]->gotHeal(this, fElapsedTime);
		}
	}
	//HEAL

	//GRENADE
	if (GrenadeIndicator > 0) {
		for (int i = 0; i < heros.size(); i++) {
			heros[i]->gotGrenade(this, fElapsedTime);
		}
	}

	//GRENADE

	//THE PLAYER
	SetPixelMode(olc::Pixel::ALPHA);
	olc::GFX2D::Transform2D t;
	t.Translate(-manSprite.getSprite()->width / 2, -manSprite.getSprite()->height / 2);
	for (int j = 0; j < heros.size(); ++j) {
		heros[j]->HeroRotate(&t, this);
		heros[j]->HeroTranslate(&t);
	}
	olc::GFX2D::DrawSprite(manSprite.getSprite().get(), t);

	


	//CROSSHAIR
	DrawLine(GetMouseX() - 5, GetMouseY(), GetMouseX() + 5, GetMouseY(), olc::RED);
	DrawLine(GetMouseX(), GetMouseY() - 5, GetMouseX(), GetMouseY() + 5, olc::RED);
	//CROSSHAIR

	//DRAW BULLETS
	for (auto a : bullets)
	{
		a->drawBullet(this);
	}

	//DRAW GRENADES
	for (auto a : grenades) {
		a->DrawSprite(this);
	}

	//DRAW ENEMIES
	for (auto a : enemies) {
		a->DrawSprite(this);
		//DrawCircle(a.x, a.y, 1, olc::RED);
		a->DrawEntityHpBar(this);
	}

	//DRAW DOG
	for (auto a : dogs) {
		a->DrawSprite(this);
	}


	//DRAW BONUSES
	for (auto a : bonuses)
	{	
		a->DrawSprite(this);
	}

	//DRAW HP BAR
	for (int j = 0; j < heros.size(); ++j)
	{
		heros[j]->DrawEntityHpBar(this);
	}
	//DRAWING
	return true;

}

