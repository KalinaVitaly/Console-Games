#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>

using namespace std;

int turn, figure_type, score = 0;
vector<pair<int, int>> figure;
vector<pair<int, int>> heap;
pair<int, int> figure_center;
bool game_continue = true;

bool IsFigureIndex(int x, int y);
bool IsHeapIndex(int x, int y);
bool IsHeapAndFigureIndex(int indexX, int indexY);
void ChangeIndex(int plane, int shift);
void FindAndDeleteFullLine();
bool CompairPairs(pair<int, int> i, pair<int, int> j) { return i.first<j.first; }
void MoveDownHeapElements(pair<int, int> line_number);
bool CanRotate(vector<pair<int, int>> new_figure_position);
pair<int, int> RotationFigure(pair<int, int> current_figure_index);
void MoveDown();

void Setup()
{
	turn = rand() % 4 + 1;
	figure_type = rand() % 7 + 1;
	switch (figure_type)
	{
	case 1:
	{
		figure.push_back(make_pair(0, 10));
		figure.push_back(make_pair(0, 11));
		figure.push_back(make_pair(1, 10));
		figure.push_back(make_pair(1, 11));
		figure_center = make_pair(0, 11);
		break;
	}
	case 2:
	{
		figure.push_back(make_pair(0, 8));
		figure.push_back(make_pair(0, 9));
		figure.push_back(make_pair(0, 10));
		figure.push_back(make_pair(0, 11));
		figure_center = make_pair(0, 10);
		break;
	}
	case 3:
	{
		figure.push_back(make_pair(0, 8));
		figure.push_back(make_pair(0, 9));
		figure.push_back(make_pair(1, 9));
		figure.push_back(make_pair(1, 10));
		figure_center = make_pair(0, 9);
		break;
	}
	case 4:
	{
		figure.push_back(make_pair(1, 8));
		figure.push_back(make_pair(0, 9));
		figure.push_back(make_pair(1, 9));
		figure.push_back(make_pair(0, 10));
		figure_center = make_pair(0, 9);
		break;
	}
	case 5:
	{
		figure.push_back(make_pair(1, 8));
		figure.push_back(make_pair(0, 8));
		figure.push_back(make_pair(0, 9));
		figure.push_back(make_pair(0, 10));
		figure_center = make_pair(0, 9);
		break;
	}
	case 6:
	{
		figure.push_back(make_pair(0, 8));
		figure.push_back(make_pair(0, 9));
		figure.push_back(make_pair(0, 10));
		figure.push_back(make_pair(1, 10));
		figure_center = make_pair(0, 9);
		break;
	}
	case 7:
	{
		figure.push_back(make_pair(0, 8));
		figure.push_back(make_pair(0, 9));
		figure.push_back(make_pair(1, 9));
		figure.push_back(make_pair(0, 10));
		figure_center = make_pair(0, 9);
		break;
	}
	default:
		break;
	}
}

void Move()
{
	char key;
	if (_kbhit()) 
	{
		key = _getch();
		switch (key)
		{
		case 'a':
		{
			if ((figure[0].second >= 2 && figure[1].second >= 2 && figure[2].second >= 2 && figure[3].second >= 2) && !IsHeapAndFigureIndex(-1, 0))
			{
				ChangeIndex(1, -1);
				--figure_center.second;
			}
			break;
		}
		case 'd':
		{
			if ((figure[0].second < 14 && figure[1].second < 14 && figure[2].second < 14 && figure[3].second < 14) && !IsHeapAndFigureIndex(1, 0))
			{
				ChangeIndex(1, 1);
				++figure_center.second;
			}
			break;
		}
		case 's':
		{	
			MoveDown();
			break;
		}
		case 'w':
		{
			ChangeIndex(0, -1);
			--figure_center.first;
			break;
		}
		case 'i':
		{
			//QuickMoveDown
			while ((figure[0].first < 28 && figure[1].first < 28 && figure[2].first < 28 && figure[3].first < 28) && !IsHeapAndFigureIndex(0, 1))
			{
				ChangeIndex(0, 1);
			}
			break;
		}
		case 'q':
		{
			//rotate figure
			if (figure_type != 1)
			{
				vector<pair<int, int>> new_figure_position;
				for (pair<int, int> i : figure)
					new_figure_position.push_back(RotationFigure(i));
				if (CanRotate(new_figure_position))
					figure = new_figure_position;
				new_figure_position.clear();
			}
			break;
		}
		default:
			//game_continue = false;
			break;
		}
	}
}

inline void ChangeIndex(int plane, int shift)
{
	for (int i = 0; i < 4; ++i)
		if (plane)
			figure[i].second += shift;
		else
			figure[i].first += shift;
}

void Print() 
{
	for (int i = 2; i < 30; ++i) 
	{
		for (int j = 0; j < 16; ++j)
		{
			if (i == 2 or i == 29 or j == 0 or j == 15)
				printf_s("#");
			else if (i > 2 && IsFigureIndex(j, i))
				printf_s("*");
			else if (IsHeapIndex(j, i))
				printf_s("0");
			else
				printf_s(" ");
		}
		cout << endl;
	}
	cout << "score: " << score << endl;
}

void MoveDown()
{
	if ((figure[0].first < 28 && figure[1].first < 28 && figure[2].first < 28 && figure[3].first < 28) && !IsHeapAndFigureIndex(0, 1))
	{
		ChangeIndex(0, 1);
		++figure_center.first;
	}
	else
	{
		for (auto i : figure)
		{
			if (i.first <= 2)
			{
				game_continue = false;
				break;
			}
			heap.push_back(pair<int, int>(i.first, i.second));
		}

		sort(heap.begin(), heap.end(), CompairPairs);
		FindAndDeleteFullLine();
		figure.clear();
		Setup();
	}
}

int main() 
{
	int start, end = start = clock();
	Setup();
	while (game_continue)
	{
		system("cls");
		Move();
		Print();
		if ((end - start) / CLOCKS_PER_SEC >= 1)
		{
			start = clock();
			MoveDown();
		}
		end = clock();
	}
	cout << "Game over!" << endl << "Your score: " << score;
	return 0;
}

bool IsHeapIndex(int x, int y) 
{
	for (pair<int, int> i : heap)
		if (i.first == y && i.second == x)
			return true;
	return false;
}

bool IsHeapAndFigureIndex(int indexX, int indexY)
{
	for (auto i : heap)
	for (int j = 0; j < 4; ++j)
		if (i.first == figure[j].first + indexY && i.second == figure[j].second + indexX)
			return true;
	return false;
}

inline bool IsFigureIndex(int x, int y)
{
	for (int i = 0; i < 4; ++i)
		if (figure[i].first == y && figure[i].second == x)
			return true;
	return false;
}

void FindAndDeleteFullLine()
{
	pair<vector<pair<int, int>> :: iterator, vector<pair<int, int>> :: iterator> bounds;
	sort(figure.begin(), figure.end(), CompairPairs);
	for (int i = 0; i < 4; i++)
	{
		bounds = equal_range(begin(heap), end(heap), figure[i], CompairPairs);
		if ((bounds.second - bounds.first) == 14)
		{
			score += 1;
			heap.erase(remove_if(begin(heap), end(heap), [i](pair<int, int> j) { return j.first == figure[i].first; }), end(heap));
			heap.shrink_to_fit();
			MoveDownHeapElements(figure[i]);
		}
	}
}

void MoveDownHeapElements(pair<int, int> line_number)
{
	vector<pair<int, int>> ::iterator bound = upper_bound(begin(heap), end(heap), line_number, CompairPairs);
	for (auto iter = heap.begin(); iter != bound; ++iter)
		++(iter->first);
}

bool CanRotate(vector<pair<int, int>> new_figure_position)
{
	for (pair<int, int> i : new_figure_position)
		if (IsHeapIndex(i.second, i.first) || i.first >= 27 || i.second < 1 || i.second > 13)
			return false;
	return true;
}

pair<int, int> RotationFigure(pair<int, int> current_figure_index)
{
	return make_pair(current_figure_index.second + figure_center.first - figure_center.second,
		figure_center.first + figure_center.second - current_figure_index.first);
}
