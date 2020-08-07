#include "ShootingGame.h"
#include "Bonus.h"
#include <iostream>
using namespace std;

Bonus::Bonus(double xIn, double yIn,ShootingGame* shootIn) : Entity(xIn, yIn, shootIn) {

}

double Bonus::BonusCheck(double heroX, double heroY) {
	return sqrt(pow(x - heroX, 2) + pow(y - heroY, 2));
};