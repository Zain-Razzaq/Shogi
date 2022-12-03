#include "King.h"

King::King(Board* b, int _cr, int _cc, Color cl)
{
    Piece::b = b;
    Piece::cr = _cr;
    Piece::cc = _cc;
    Piece::C = cl;

    if (C == W)
    {
        img = "King-W.png";
        Name = 'k';
    }
    else
    {
        img = "King-B.png";
        Name = 'K';

    }
}
void King::print(sf::RenderWindow& window)
{
    sf::Texture temp;
    if (!temp.loadFromFile(img))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s(temp);
    s.setScale(0.9, 0.9);

    s.setPosition((cc * 100) + 10, (cr * 100) + 5);
    window.draw(s);
}
bool King::IsLegal(int row1, int col1, int row2, int col2)
{
	int Dr, Dc;
	Dr = abs(row2 - row1);
	Dc = abs(col2 - col1);
	return(((Dr == 1 && Dc == 0) || (Dr == 0 && Dc == 1) || (Dr == 1 && Dc == 1)));
}


void King::Promotion(sf::RenderWindow& window)
{
    return;
}
