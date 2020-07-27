#pragma once

#include "Car.h"
#include <string>

class Ford : public Car
{
public:
	Ford(double _delta_speed, double _max_speed, std::string _name = "unknown");

	void Bonus() override;
};

//class Ferrari : public Car
//{
//public:
//	Ferrari(double _deltaspeed, double _max_speed, string _name = "unknown")
//		: Car(_deltaspeed, _max_speed, _name) {};
//
//	void Bonus() override;
//};

