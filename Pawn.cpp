#include "Header.h"
#include "Piece.h"
#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(Board * b,int _cr,int _cc, Color cl,bool pm)
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
            Name = '^';
            img = "Pawn-WP.png";
        }
        else if (C == B )
        {
            Name = '+';
            img = "Pawn-BP.png";
        }
    }
    else
    {
        if (C == W)
        {
            img = "Pawn-W.png";
            Name = 'p';
        }
        else
        {
            img = "Pawn-B.png";
            Name = 'P';
        }
    }
}


void Pawn::print(sf::RenderWindow& window)
{
    sf::Texture temp;
    if (!temp.loadFromFile(img))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s(temp);
    s.setScale(0.85, 0.85);

    s.setPosition((cc * 100) + 20, (cr * 100) + 10);
    window.draw(s);

}


bool Pawn::IsLegal(int row1, int col1, int row2, int col2)
{
    int Dr, Dc;

    if (promoted)
    {
        Dr = (row2 - row1);
        Dc = (col2 - col1);
        if (C == W)
        {
            if (Dr == 1 && (Dc != 0))
                return false;

        }
        else if (C == B)
        {
            if (Dr == -1 && Dc != 0)
                return false;
        }
        Dr = abs(Dr);
        Dc = abs(Dc);

        return(((Dr == 1 && Dc == 0) || (Dr == 0 && Dc == 1) || (Dr == 1 && Dc == 1)));
    }



    Dr = row1 - row2;
    Dc = col1 - col2;
	if (C == W)
	{
        
        if (Dr == 2 && Dc == 0 && row1 == 6)
        {
            return (IsVerClear(row2 - 1, col2));
        }
        else if (Dr == 1 && Dc == 0)
        {
            return (IsVerClear(row2 - Dr, col2));
        }
        else if (((Dc == 1 || Dc == -1) && Dr == 1))
        {
            return (!IsDiagonalClear(row2 - Dr, col2 - Dc));
        }
        else {
            return false;
        }
	}
    else
    {
        if (Dr == -2 && Dc == 0 && row1 == 2)
        {
            return (IsVerClear(row2 + 1, col2));
        }
        else if (Dr == -1 && Dc == 0 )
        {
            return (IsVerClear(row2 - Dr, col2));
        }
        else if (((Dc == 1 || Dc == -1) && Dr == -1))
        {
            return (!IsDiagonalClear(row2 - Dr, col2 - Dc));
        }
        else {
            return false;
        }
    }
}

void Pawn::Promotion(sf::RenderWindow& window)
{
    if (!promoted)
    {
        if (C == W && (cr == 2 || cr==1))
        {
            if (first)
            {
                bool p;
                p = AskForPromotion(window);
                if (p)
                {
                    Name = '^';
                    img = "Pawn-WP.png";
                    promoted = true;
                }
                first = false;
            }
        }
        else if (C == W && cr == 0)
        {
            Name = '^';
            img = "Pawn-WP.png";
            promoted = true;
        }
        else if (C == B && (cr == 6 || cr == 7))
        {
            if (first)
            {
                bool p;
                p = AskForPromotion(window);
                if (p)
                {
                    Name = '+';
                    img = "Pawn-BP.png";
                    promoted = true;
                }
                first = false;
            }
        }
        else if (C == B && cr == 8)
        {
            Name = '+';
            img = "Pawn-BP.png";
            promoted = true;
        }
        
    }
    
}