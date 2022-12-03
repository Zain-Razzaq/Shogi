#include "Piece.h"
#include"Header.h"
#include "Board.h"

Piece::Piece(Board* b,int _cr,int _cc,Color _c):cr(_cr),cc(_cc),C(_c),b(b)
{ }


bool Piece::MyPiece(int color)
{
    if (C==W && color==0)
    {
        return true;
    }
    if (C==B && color==1)
    {
        return true;
    }
    return false;
}


char Piece::getName()
{
    return Name;
}

bool Piece::isPromoted()
{
    return promoted;
}



bool Piece::IsHorMove(int row2, int col2)
{
    return(cr == row2);
}

bool Piece::IsVerMove(int row2, int col2)
{
    return(cc == col2);
}

bool Piece::IsDiagonalMove(int row2, int col2)
{
    int Dr, Dc;
    Dr = abs(row2 - cr);
    Dc = abs(col2 - cc);
    return(Dr == Dc);
}

bool Piece::IsHorClear(int row2, int col2)
{
    int sc, ec;
    if (col2 > cc)
    {
        sc = cc + 1;
        ec = col2 - 1;
    }
    else
    {
        sc = col2 + 1;
        ec = cc - 1;
    }
    for (int i = sc; i <= ec; i++)
    {
        if (b->Box[cr][i] != nullptr)
        {
            return false;
        }
        
    }
    return true;
}

bool Piece::IsVerClear(int row2, int col2)
{
    int sr, er;
    if (row2 > cr)
    {
        sr = cr + 1;
        er = row2 - 1;
    }
    else
    {
        sr = row2 + 1;
        er = cr - 1;
    }
    for (int i = sr; i <= er; i++)
    {
        if (b->Box[i][cc] != nullptr)
        {
            return false;
        }
    }
    return true;
}

bool Piece::IsDiagonalClear(int row2, int col2)
{
    int t = abs(row2 - cr);
    int sr, sc, er, ec;
    if (cr > row2 && cc > col2)
    {
        sr = row2 + 1;
        er = cr - 1;
        sc = col2 + 1;
        ec = cc - 1;
    }
    
    if (cr < row2 && cc < col2)
    {
        sr = cr + 1;
        er = row2 - 1;
        sc = cc + 1;
        ec = col2 - 1;
    }
    if ((cr > row2 && cc > col2) || (cr < row2 && cc < col2))
    {
        for (int i = 0; i < t - 1; i++)
        {
            if (b->Box[sr + i][sc + i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }



    if (cr > row2 && cc < col2)
    {
        sr = cr - 1;
        er = row2 + 1;
        sc = cc + 1;
        ec = col2 - 1;
    }
    if (cr<row2 && cc>col2)
    {
        sr = row2 - 1;
        ec = cr + 1;
        sc = col2 + 1;
        ec = cc - 1;
    }
    if ((cr > row2 && cc < col2) || (cr<row2 && cc>col2))
    {
        for (int i = 0; i < t - 1; i++)
        {
            if (b->Box[sr - i][sc + i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }


}

void Piece::Move(int row1, int col1, int row2, int col2,bool tempMove)
{

    

    if (b->Box[row2][col2]!=nullptr && !tempMove)
    {
        if (b->Box[row2][col2]->Name == 'p' || b->Box[row2][col2]->Name == '^')
        {
            b->Captured[0][2]++;
        }
        else if (b->Box[row2][col2]->Name == 'P' || b->Box[row2][col2]->Name == '+')
        {
            b->Captured[1][2]++;
        }
        else if (b->Box[row2][col2]->Name == 'g')
        {
            b->Captured[0][0]++;
        }
        else if (b->Box[row2][col2]->Name == 'G')
        {
            b->Captured[1][0]++;
        }
        else if (b->Box[row2][col2]->Name == 's' || b->Box[row2][col2]->Name == '%')
        {
            b->Captured[0][1]++;
        }
        else if (b->Box[row2][col2]->Name == 'S' || b->Box[row2][col2]->Name == '_')
        {
            b->Captured[1][1]++;
        }
        else if (b->Box[row2][col2]->Name == 'b' || b->Box[row2][col2]->Name == '!')
        {
            b->Captured[0][3]++;
        }
        else if (b->Box[row2][col2]->Name == 'B' || b->Box[row2][col2]->Name == '&')
        {
            b->Captured[1][3]++;
        }
        else if (b->Box[row2][col2]->Name == 'r' || b->Box[row2][col2]->Name == '@')
        {
            b->Captured[0][4]++;
        }
        else if (b->Box[row2][col2]->Name == 'R' || b->Box[row2][col2]->Name == '*')
        {
            b->Captured[1][4]++;
        }
        else if (b->Box[row2][col2]->Name == 'l' || b->Box[row2][col2]->Name == '#')
        {
            b->Captured[0][5]++;
        }
        else if (b->Box[row2][col2]->Name == 'L' || b->Box[row2][col2]->Name == '(')
        {
            b->Captured[1][5]++;
        }
        else if (b->Box[row2][col2]->Name == 'h' || b->Box[row2][col2]->Name == '$')
        {
            b->Captured[0][6]++;
        }
        else if (b->Box[row2][col2]->Name == 'H' || b->Box[row2][col2]->Name == ')')
        {
            b->Captured[1][6]++;
        }






        //delete[] b->Box[row2][col2];
    }

    b->Box[row2][col2] = b->Box[row1][col1];
    b->Box[row2][col2]->cr = row2;
    b->Box[row2][col2]->cc = col2;
    b->Box[row1][col1] = nullptr;

    
    
}

void Piece::highlight(sf::RenderWindow& window)
{
    sf::Texture temp;
    if (!temp.loadFromFile("Border.png"))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s(temp);
    s.setScale(1, 1);
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if ((b->Box[x][y]==nullptr || !b->Box[x][y]->MyPiece(C)) && ((IsLegal(cr, cc, x, y))) &&  (!b->selfCheak(b->row1,b->col1,x,y)))
            {
                s.setPosition((y * 100), (x * 100)+3);
                window.draw(s);
                window.display();
                window.draw(s);

                window.display();
            }
        }
    }
}


bool Piece::AskForPromotion(sf::RenderWindow& window)
{
    sf::Texture t;
    t.loadFromFile("PromotionCheck.jpg");
    sf::Sprite Promot(t);
    Promot.setPosition(300, 300);
    window.display();
    window.draw(Promot);
    window.display();
    int r, c;
    while (true)
    {
        getRowColbyLeftClick(r, c, window);
        if (c>=80+300 && r>=190+300 && c<=220+300 && r<=250+300)
        {
            return true;
        }
        else if(c >= 285+300 && r >= 190+300 && c <= 427+300 && r <= 250+300)
        {
            return false;
        }
    }
}


