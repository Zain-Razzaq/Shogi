#include "Header.h"
#include "Player.h"

Player::Player(string n, int color):name(n)
{
	if (color == 0)
		this->C = W;
	else
		this->C = B;
}


Player::Player(const Player& A)
{
	name = A.name;
	C = A.C;
}


Color Player::getClr()
{
	return C;
}

string& Player::getName()
{
	return this->name;
}
