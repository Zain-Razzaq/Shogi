#pragma once

#include"Header.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class  Board;


class Piece
{
protected:
	Color C=W;
	Board * b=nullptr;
	string img={};
	char Name = NULL;
	int cr=0, cc=0;
	bool promoted;
	bool first = true;
public:
	Piece(){};
	Piece(Board* b,int _cr,int _cc,Color _c);
	bool MyPiece(int color);
	bool isPromoted();
	char getName();
	virtual void print(sf::RenderWindow& window) = 0;
	virtual bool IsLegal(int row1, int col1, int row2, int col2) { return false; };
	void highlight(sf::RenderWindow& window);
	void Move(int row1, int col1, int row2, int col2, bool tempMove = false);
	bool IsHorMove(int row2, int col2);
	bool IsVerMove(int row2, int col2);
	bool IsDiagonalMove(int row2, int col2);
	bool IsHorClear(int row2, int col2);
	bool IsVerClear(int row2, int col2);
	bool IsDiagonalClear(int row2, int col2);
	bool AskForPromotion(sf::RenderWindow& window);
	virtual void Promotion(sf::RenderWindow& window) = 0;


};

