#pragma once
#include"Header.h"

#include <iostream>
#include<string>

#include <SFML/Graphics.hpp>

class Piece;
class Player;

using namespace std;

class Board
{
	Player** Ps;
	Piece*** Box;
	int row1, col1, row2, col2;
	bool turn;
	char pieceToDrop;
	int** Captured;
	sf::Font font;
	sf::Text text;

	friend class Piece;
	
public:
	Board();
	void SetBoard(string fileName, int  FromFile=false, string P1="z", string P2="a");
	bool IsValidSourceSelection(int row, int col);
	bool IsValidDestSelection(int row, int col);
	void DisplayBoard(sf::RenderWindow& window);
	void select_src(bool& newGame, bool& isUndo, sf::RenderWindow& window);
	void select_des(bool& newGame, bool& isUndo, sf::RenderWindow& window);
	bool isLegalMove(int row1, int col1, int row2, int col2);
	void Findking(int& kr, int& kc,bool t);
	bool check(bool t);
	bool selfCheak(int row1,int col1,int row2,int col2);
	bool canImove();
	void pawnPromotion(sf::RenderWindow& window);
	void PieceDroping();

	void DropThePiece();


	void saveInFile(string fn);





	int RunBoard(sf::RenderWindow& window);


};

