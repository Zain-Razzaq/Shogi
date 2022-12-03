#pragma once
#include "Piece.h"
#include "SFML/Graphics.hpp"
class GoldenGeneral :
    public Piece
{
public:
    GoldenGeneral(Board* b, int _cr, int _cc, Color cl);
    void print(sf::RenderWindow& window);
    bool IsLegal(int row1, int col1, int row2, int col2);
    void Promotion(sf::RenderWindow& window);
};

