#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#define ROAD_LENGTH 15

using namespace std;

int main()
{

	return 0;
}

class Random
{
public:
	Random() = delete;
	static int getIntRand(int min, int max)
	{
		return min + rand() % max + 1;
	}
	static double getDoubleRand(double min, double max)
	{
		return min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
	}
};

class Car
{
private:
	double speed;
	double max_speed;
	double delta_speed;
	double position;
	string racer;

public:
	Car(double _delta_speed, double _max_speed, string _name)
		: delta_speed{ _delta_speed }, speed { 0 }, position{ 0 }, racer{ _name }, max_speed{ _max_speed } {};
	
	bool move() {};
	double updateSpeed() {};

	void setSpeed(double _speed) { speed = _speed; }
	void setPosition(int _position) { position = _position; }

	double getSpeed() { return speed; }
	double getDeltaSpeed() { return delta_speed; }
	double getMaxSpeed() { return max_speed; }
	int getPosition() { return position; }

	virtual void Bonus() = 0;
};

class Ford : public Car
{	
public:
	Ford(double _delta_speed, double _max_speed, string _name = "unknown")
		: Car(_delta_speed, _max_speed, _name) {};

	virtual void Bonus() override;
};

class Ferrari : public Car
{
public:
	Ferrari(double _deltaspeed, double _max_speed, string _name = "unknown")
		: Car(_deltaspeed, _max_speed, _name) {};

	virtual void Bonus() override;
};

double Car::updateSpeed()
{
	double new_speed = Random::getDoubleRand(getSpeed(), getDeltaSpeed());
	
	if (new_speed <= getMaxSpeed())
		setSpeed(new_speed);
	
	return getSpeed();
}


bool Car::move()
{
	position += getSpeed();

	if (static_cast<int>(position) >= ROAD_LENGTH)
		return true;

	return false;
}
/*
void print(const Car& car)
{
	for (int i = 0; i < ROAD_LENGTH + 3; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			if (i == 0)
		}
	}
}
*/