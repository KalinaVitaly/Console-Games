#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

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
	int position;
	string racer;

public:
	Car(double _delta_speed, double _max_speed, int _position, string _name)
		: delta_speed{ _delta_speed }, speed { 0 }, position{ _position }, racer{ _name }, max_speed{ _max_speed } {};
	
	virtual void move() {};
	virtual double updateSpeed() {};

	void setSpeed(double _speed) { speed = _speed; }
	void setPosition(int _position) { position = _position; }

	double getSpeed() { return speed; }
	double getDeltaSpeed() { return delta_speed; }
	int getPosition() { return position; }
};

class Ford : public Car
{	
public:
	Ford(double _delta_speed, double _max_speed, int _position = 0, string _name = "unknown")
		: Car(_delta_speed, _max_speed, _position, _name) {};

	virtual void move() override;
	virtual double updateSpeed() override;
};

class Ferrari : public Car
{
public:
	Ferrari(double _deltaspeed, double _max_speed, int _position = 0, string _name = "unknown")
		: Car(_deltaspeed, _max_speed, _position, _name) {};

	virtual void move() override;
	virtual double updateSpeed() override;
};


void Ford::move()
{

}

void Ferrari::move()
{

}

double Ford::updateSpeed()
{
	double new_speed = Random::getDoubleRand(getSpeed(), getDeltaSpeed());
	setSpeed(new_speed);
	return new_speed;
}

double Ferrari::updateSpeed()
{

}

void print(const Car& car)
{

}
