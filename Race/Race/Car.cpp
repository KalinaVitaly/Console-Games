#include "Car.h"
#include "Random.h"

Car::Car(double _delta_speed, double _max_speed, std::string _name)
	: delta_speed{ _delta_speed }, speed{ 0 }, position{ 0 }, racer{ _name }, max_speed{ _max_speed }, moving_direction{ 1 } {};


Car::~Car()
{
}

double Car::updateSpeed()
{
	
	return getSpeed();
}


bool Car::move()
{
	
	return false;
}
