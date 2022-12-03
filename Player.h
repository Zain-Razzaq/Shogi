#pragma once

#include"Header.h"

#include <string>

using namespace std;

class Player
{
	string name;
	Color C;
public:
	Player(const Player& A);
	Player(string n, int color);
	Color getClr();
	string& getName();
};

