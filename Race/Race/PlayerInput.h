#pragma once

#include <conio.h>
#include "Car.h"

class PlayerInput
{
public:
	PlayerInput() = delete;

	static void getPlayerInput(Car& car);
};

