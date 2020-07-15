#include <iostream>
#include <algorithm>
#include <chrono>
#include <conio.h>
#include <Windows.h>

using namespace std;

const unsigned cg_map_length = 20;
const unsigned cg_map_width = 15;
unsigned g_snake_body_size;
unsigned score;
unsigned speed;
pair<unsigned, unsigned> g_snake_body_index[600];
pair<unsigned, unsigned> g_fruit_index;

void print();
void setupStartPosition();
void update(unsigned short moving_direction);
void getPlayerInput(unsigned short& moving_direction);
bool isGameOver();
bool isSnakeCoordinate(const pair<unsigned short, unsigned short>& cor);

int main()
{
	bool is_game_continue = true;
	unsigned short moving_direction = 1;
	setupStartPosition();

	while (is_game_continue)
	{
		auto begin = chrono::steady_clock::now();
		auto end = begin;
		print();

		do
		{
			getPlayerInput(moving_direction);
			end = chrono::steady_clock::now();

		} while (chrono::duration_cast<chrono::milliseconds>(end - begin).count() < 1000.0 / speed);
		
		update(moving_direction);
		is_game_continue = !isGameOver();


		system("cls");
	}
	print();
	system("pause");


	return 0;
}

bool isSnakeCoordinate(const pair<unsigned short, unsigned short>& cor)
{
	for (unsigned short i = 0; i < g_snake_body_size; ++i)
	{
		if (g_snake_body_index[i].first == cor.first - 1 && g_snake_body_index[i].second == cor.second - 1)
		{
			return true;
		}	
	}
	return false;
}

void getPlayerInput(unsigned short& moving_direction)
{
	char key;
	if (_kbhit())
	{
		key = _getch();
		switch (key)
		{
		case 'w':
		{
			if (moving_direction != 3)
			{
				moving_direction = 1;
			}
			break;
		}
		case 'a':
		{
			if (moving_direction != 2)
			{
				moving_direction = 0;
			}

			break;
		}
		case 's':
		{
			if (moving_direction != 1)
			{
				moving_direction = 3;
			}
				 
			break;
		}
		case 'd':
		{
			if (moving_direction != 0)
			{
				moving_direction = 2;
			}

			break;
		}
		default:
			break;
		}
	}
}

void print() 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (unsigned i = 0; i < cg_map_length + 2; ++i)
	{
		for (unsigned j = 0; j < cg_map_width + 2; ++j)
		{

			if (i == g_fruit_index.first + 1 && j == g_fruit_index.second + 1)
			{
				SetConsoleTextAttribute(hConsole, 2);
				cout << "$";
			}
			else if (i == 0 || i == cg_map_length + 1 || j == 0 || j == cg_map_width + 1)
			{
				SetConsoleTextAttribute(hConsole, 4);
				cout << "#";
			}
			else if (g_snake_body_index + g_snake_body_size != find(g_snake_body_index, g_snake_body_index + g_snake_body_size, make_pair(i - 1, j - 1)))
			{
				SetConsoleTextAttribute(hConsole, 11);
				cout << "0";
			}
			else
				cout << " ";
		}
		cout << endl;
	}
	//output snake coordinate
	/*for (unsigned short i = 0; i < g_snake_body_size; ++i)
	{
		cout << g_snake_body_index[i].first << " : " << g_snake_body_index[i].second << endl;
	}*/

}

void setupStartPosition()
{
	g_snake_body_size = 1;
	g_fruit_index.first = rand() % 20;
	g_fruit_index.second = rand() % 15;
	g_snake_body_index[0].first = cg_map_length / 2;
	g_snake_body_index[0].second = cg_map_width / 2;
	score = 0;
	speed = 10;
}

void update(unsigned short moving_direction)
{
	for (unsigned short i = g_snake_body_size; i > 0 ; --i)
	{
		g_snake_body_index[i] = g_snake_body_index[i - 1];
	}

	switch (moving_direction)
	{
	case 0:
	{
		--g_snake_body_index[0].second;
		break;
	}
	case 1:
	{
		--g_snake_body_index[0].first;
		break;
	}
	case 2:
	{
		++g_snake_body_index[0].second;
		break;
	}
	case 3:
	{
		++g_snake_body_index[0].first;
		break;
	}
	default:
		break;
	}

	if (g_snake_body_index[0].first == g_fruit_index.first && g_snake_body_index[0].second == g_fruit_index.second)
	{
		g_fruit_index.second = rand() % 15;
		g_fruit_index.first = rand() % 20;
		++score;
		++g_snake_body_size;

		if (score % 10 == 0)
			speed += 10;
	}
}

bool isGameOver()
{
	for (unsigned short i = 0; i < g_snake_body_size; ++i)
	{
		pair<unsigned, unsigned> *fresult = find_if(g_snake_body_index, g_snake_body_index + g_snake_body_size, 
			[](const pair<unsigned, unsigned> body) { return (body.first == -1 ||
			body.first == cg_map_length || body.second == -1 || body.second == cg_map_width);});
		
		if (fresult != g_snake_body_index + g_snake_body_size)
			return true;
	}

	return false;
}
