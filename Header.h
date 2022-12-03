#pragma once

enum Color { W, B };

#define NOMINMAX 

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
// #include <windows.h>
// #include <conio.h>
// #include "SFML/Graphics.hpp"
#include "SFML-2.5.1/include/SFML/Graphics.hpp"

using namespace std;


#define BLACK 0
#define WHITE 15
#define BROWN 6
#define GREEN 2
#define RED 4
#define LBLUE 9

struct Position
{
	int x,y;
};

// void static SetClr(int tcl, int bcl)
// {
// 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
// }

void static getRowColbyLeftClick(int& rpos, int& cpos, sf::RenderWindow& window)
{
	while (true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i p = sf::Mouse::getPosition(window);
			
			cpos = p.x;
			rpos = p.y;
			break;
		}
	}
}



// void static gotoRowCol(int rpos, int cpos)
// {
// 	COORD scrn;
// 	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
// 	scrn.X = cpos;
// 	scrn.Y = rpos;
// 	SetConsoleCursorPosition(hOuput, scrn);
// }