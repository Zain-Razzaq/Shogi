#include "Bishop.h"



Bishop::Bishop(Board* b, int _cr, int _cc, Color cl,bool pm)
{
    Piece::b = b;
    Piece::cr = _cr;
    Piece::cc = _cc;
    Piece::C = cl;
    Piece::promoted = pm;

    if (promoted)
    {
        if (C == W)
        {
            Name = '!';
            img = "Bishop-WP.png";
        }
        else if (C == B)
        {
            Name = '&';
            img = "Bishop-BP.png";
        }
    }
    else
    {
        if (C == W)
        {
            img = "Bishop-W.png";
            Name = 'b';
        }
        else
        {
            img = "Bishop-B.png";
            Name = 'B';

        }
    }
}


void Bishop::print(sf::RenderWindow& window)
{
    sf::Texture temp;
    if (!temp.loadFromFile(img))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s(temp);
    s.setScale(1, 0.9);

    s.setPosition((cc * 100) + 5,(cr * 100)+3);
    window.draw(s);
}


bool Bishop::IsLegal(int row1, int col1, int row2, int col2)
{
    if(promoted)
    {
        bool temp = IsDiagonalMove(row2, col2) && IsDiagonalClear(row2, col2);
        if (temp)
            return temp;

        int Dr, Dc;
        Dr = abs(row2 - row1);
        Dc = abs(col2 - col1);
        return(((Dr == 1 && Dc == 0) || (Dr == 0 && Dc == 1) || (Dr == 1 && Dc == 1)));
    }

	return(IsDiagonalMove(row2, col2) && IsDiagonalClear(row2, col2));

}


void Bishop::Promotion(sf::RenderWindow& window)
{
    if (!promoted)
    {

        if (C == W && cr < 3)
        {
            if (AskForPromotion(window))
            {
                Name = '!';
                img = "Bishop-WP.png";
                promoted = true;
            }

        }
        else if (C == B && cr > 5)
        {
            if (AskForPromotion(window))
            {
                Name = '&';
                img = "Bishop-BP.png";
                promoted = true;
            }
            
        }
    }
}


