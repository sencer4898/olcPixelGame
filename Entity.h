#pragma once
#include <memory>

using namespace std;

class ShootingGame;
class SpriteClass;

class Entity 
{
protected:
	double x;
	double y;
	ShootingGame* shoot;
public:
	Entity(double xIn, double yIn, ShootingGame* shootIn);
	double distance(shared_ptr<Entity> OtherEntity);
	double distanceCalculator(int a, int b);
	virtual void DrawSprite(ShootingGame* theGame)=0;
	double directionFinderX(int a);
	double directionFinderY(int a);
};