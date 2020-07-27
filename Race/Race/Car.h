#pragma once
#include <string>


class Car
{
private:
	int moving_direction;

	double speed;
	double max_speed;
	double delta_speed;
	double position;

	std::string racer;

public:
	Car(double _delta_speed, double _max_speed, std::string _name);
	~Car();
	
	bool move();
	double updateSpeed();

	void setSpeed(double _speed) { speed = _speed; }
	void setPosition(int _position) { position = _position; }
	void setMovingDirection(int _moving_direction) { moving_direction = _moving_direction; }

	double getSpeed() { return speed; }
	double getDeltaSpeed() { return delta_speed; }
	double getMaxSpeed() { return max_speed; }
	double getPosition() { return position; }
	int getDirection() { return moving_direction; }

	virtual void Bonus() = 0;
};
