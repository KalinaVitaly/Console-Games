#include "PlayerInput.h"

void PlayerInput::getPlayerInput(Car& car)
{
	char key;
	if (_kbhit())
	{
		key = _getch();
		switch (key)
		{
		case 'w':
		{
			if (car.getDirection() != 3)
			{
				car.setMovingDirection(1);
			}
			break;
		}
		case 'a':
		{
			if (car.getDirection() != 2)
			{
				car.setMovingDirection(0);
			}

			break;
		}
		case 's':
		{
			if (car.getDirection() != 1)
			{
				car.setMovingDirection(3);
			}

			break;
		}
		case 'd':
		{
			if (car.getDirection() != 0)
			{
				car.setMovingDirection(2);
			}

			break;
		}
		default:
			break;
		}
	}
}