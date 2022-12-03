#pragma once

#include "Piece.h"

//class Piece;

//class Board;


class Pawn: public Piece
{
protected:

public:
    Pawn(Board* b, int _cr, int _cc, Color cl, bool pm = false);
    void print(sf::RenderWindow& window);
    bool IsLegal(int row1, int col1, int row2, int col2);
    void Promotion(sf::RenderWindow& window);
};

