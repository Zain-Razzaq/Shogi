#include "Rook.h"


Rook::Rook(Board* b, int _cr, int _cc, Color cl,bool pm)
{
    Piece::b = b;
    Piece::cr = _cr;
    Piece::cc = _cc;
    Piece::C = cl;
    Piece::promoted = pm;
    if (promoted)
    {
        if (C == W )
        {
            Name = '@';
            img = "Rook-WP.png";
        }
        else if (C == B )
        {
            Name = '*';
            img = "Rook-BP.png";
        }
    }
    else
    {
        if (C == W)
        {
            img = "Rook-W.png";
            Name = 'r';
        }
        else
        {
            img = "Rook-B.png";
            Name = 'R';
        }
    }
}
void Rook::print(sf::RenderWindow& window)
{
    sf::Texture temp;
    if (!temp.loadFromFile(img))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s(temp);
    s.setScale(0.85, 0.85);

    s.setPosition((cc * 100) + 15, (cr * 100) + 12);
    window.draw(s);

}
bool Rook::IsLegal(int row1, int col1, int row2, int col2)
{

    if (promoted)
    {
        bool temp = (IsHorMove(row2, col2) && IsHorClear(row2, col2)) || (IsVerMove(row2, col2) && IsVerClear(row2, col2));
        if (temp)
            return temp;

        int Dr, Dc;
        Dr = abs(row2 - row1);
        Dc = abs(col2 - col1);
        return(((Dr == 1 && Dc == 0) || (Dr == 0 && Dc == 1) || (Dr == 1 && Dc == 1)));
    }



	return((IsHorMove(row2, col2) && IsHorClear(row2, col2)) || (IsVerMove(row2, col2) && IsVerClear(row2, col2)));
}

void Rook::Promotion(sf::RenderWindow& window)
{

    if (!promoted)
    {

        if (C == W && cr < 3)
        {
            if (AskForPromotion(window))
            {
                Name = '@';
                img = "Rook-WP.png";
                promoted = true;
            }

        }
        else if (C == B && cr > 5)
        {
            if (AskForPromotion(window))
            {
                Name = '*';
                img = "Rook-BP.png";
                promoted = true;
            }

        }
    }
}