#include <iostream>
#include "ShootingGame.h"
#include "Entity.h"
using namespace std;


Entity::Entity(double xIn, double yIn, ShootingGame* shootIn) :x(xIn), y(yIn), shoot(shootIn) {
}


double Entity::distanceCalculator(int a, int b) {
	return sqrt(pow(x - a, 2) + pow(y - b, 2));
}

double Entity::distance(shared_ptr<Entity> OtherEntity) {
	return OtherEntity->distanceCalculator(x,y);
}



double Entity::directionFinderX(int a) {
	return x - a;
}

double Entity::directionFinderY(int a) {
	return y - a;
}
