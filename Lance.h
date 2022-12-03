#pragma once
#include "Piece.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Lance :
    public Piece
{
public:
    Lance(Board* b, int _cr, int _cc, Color cl, bool pm = false);
    void print(sf::RenderWindow& window);
    bool IsLegal(int row1, int col1, int row2, int col2);
    void Promotion(sf::RenderWindow& window);
};

