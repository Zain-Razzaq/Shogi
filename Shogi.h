#pragma once
#include "Header.h"
// #include "SFML/Graphics.hpp"
#include "Board.h"

class Shogi
{
	std::string* P;
	//sf::RenderWindow window;
	sf::Font font;
	sf::Text te;
	sf::Text text;

public:
	Shogi();
	void RunShogi();
	void EnterPlayers(sf::RenderWindow& window);

};

