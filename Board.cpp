#include "Board.h"
#include"Header.h"
#include "Player.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Lance.h"
#include "Knight.h"
#include "King.h"
#include "GoldenGeneral.h"
#include "SilverGeneral.h"

#include <fstream>

using namespace std;

Board::Board() :Ps(nullptr), Box(nullptr), row1(0), col1(0), row2(0), col2(0), turn(0)
{
    Captured = new int* [2];
    for (int i = 0; i < 2; i++)
    {
        Captured[i] = new int[7]{};
    }
    font.loadFromFile("font.otf");
    text.setFont(font);
    text.setCharacterSize(50);

}


void Board::SetBoard(string fileName, int FromFile, string P1, string P2)
{
    
    ifstream Rdr(fileName);
    char temp;


    Box = new Piece * *[9];
    for (int i = 0; i < 9; i++)
    {
        Box[i] = new Piece * [9];
        for (int j = 0; j < 9; j++)
        {
            Rdr >> temp;

            //Black

            if (temp == 'P')
                Box[i][j] = new Pawn(this, i, j, B);
            else if(temp== 'B')
                Box[i][j] = new Bishop(this, i, j, B);
            else if(temp=='R')
                Box[i][j] = new Rook(this, i, j, B);
            else if(temp=='L')
                Box[i][j] = new Lance(this, i, j, B);
            else if (temp == 'H')
                Box[i][j] = new Knight(this, i, j,B);
            else if (temp == 'K')
                Box[i][j] = new King(this, i, j,B);
            else if (temp == 'G')
                Box[i][j] = new GoldenGeneral(this, i, j,B);
            else if (temp == 'S')
                Box[i][j] = new SilverGeneral(this, i, j,B);

            // Black Promoted

            else if (temp == '&')
                Box[i][j] = new Bishop(this, i, j,B, true);
            else if (temp == '*')
                Box[i][j] = new Rook(this, i, j,B, true);
            else if (temp == '(')
                Box[i][j] = new Lance(this, i, j,B, true);
            else if (temp == ')')
                Box[i][j] = new Knight(this, i, j,B, true);
            else if (temp == '_')
                Box[i][j] = new SilverGeneral(this, i, j,B, true);
            else if (temp == '+')
                Box[i][j] = new Pawn(this, i, j,B, true);



            // White


            else if (temp == 'p')
                Box[i][j] = new Pawn(this, i, j,W);
            else if (temp=='b')
                Box[i][j] = new Bishop(this, i, j,W);
            else if (temp=='r')
                Box[i][j] = new Rook(this, i, j, W);
            else if (temp=='l')
                Box[i][j] = new Lance(this, i, j,W);
            else if (temp == 'h')
                Box[i][j] = new Knight(this, i, j,W);
            else if (temp == 'k')
                Box[i][j] = new King(this, i, j,W);
            else if (temp == 'g')
                Box[i][j] = new GoldenGeneral(this, i, j,W);
            else if (temp == 's')
                Box[i][j] = new SilverGeneral(this, i, j,W);

            //  White Promoted

            else if (temp == '!')
                Box[i][j] = new Bishop(this, i, j, W,true);
            else if (temp == '@')
                Box[i][j] = new Rook(this, i, j,W,true);
            else if (temp == '#')
                Box[i][j] = new Lance(this, i, j,W,true);
            else if (temp == '$')
                Box[i][j] = new Knight(this, i, j,W,true);
            else if (temp == '%')
                Box[i][j] = new SilverGeneral(this, i, j,W, true);
            else if (temp == '^')
                Box[i][j] = new Pawn(this, i, j, W, true);




            else
                Box[i][j] = nullptr;
        }
    }

    if (FromFile)
    {
        Rdr >> P1;
        Rdr >> P2;
        Rdr >> turn;
        
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                Rdr >> Captured[i][j];
            }
        }
    }
    
    Ps = new Player * [2];
    Ps[0] = new Player(P1, 0);
    Ps[1] = new Player(P2, 1);


   
}

bool Board::IsValidSourceSelection(int row, int col)
{
    if (row > 8 || row < 0 || col>8 || col < 0)
    {
        return 0;
    }
    if (Box[row][col]==nullptr)
    {
        return false;
    }
    return (Box[row][col]->MyPiece( Ps[turn]->getClr()));
}


bool Board::IsValidDestSelection(int row, int col)
{
    return (!IsValidSourceSelection(row, col));
}




void Board::DisplayBoard(sf::RenderWindow& window)
{
    
    sf::Texture board_texture;
    if (!board_texture.loadFromFile("board-img.png"))
    {
        throw("Unable to load board img");
    }


    sf::Sprite s(board_texture);
    s.setPosition(sf::Vector2f(0, 0));
    s.scale(sf::Vector2f(1, 1));

    window.clear();
        sf::Event event;

        while (window.pollEvent(event))
            if (event.type ==
                sf::Event::Closed)
                window.close();

        window.draw(s);


        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (Box[i][j] != nullptr)
                {
                    Box[i][j]->print(window);

                }

            }
        }

        {

            // White

            if (Captured[0][0]!=0)
            {
                sf::Texture t;
                t.loadFromFile("GG-W.png");
                sf::Sprite s(t);
                s.setScale(0.7, 0.7);

                s.setPosition(929 + 5, 42 + 5);
                window.draw(s);
            }
            if (Captured[0][1] != 0)
            {
                board_texture.loadFromFile("SG-W.png");
                sf::Sprite s(board_texture);
                s.scale(0.11, 0.11);
                s.setPosition(1041+10,42+10);
                window.draw(s);
            }
            if (Captured[0][2] != 0)
            {
                board_texture.loadFromFile("Pawn-W.png");
                sf::Sprite s(board_texture);
                s.setScale(0.85, 0.85);
                s.setPosition(1153+20,42+10);
                window.draw(s);
            }
            if (Captured[0][3] != 0)
            {
                board_texture.loadFromFile("Bishop-W.png");
                sf::Sprite s(board_texture);
                s.setScale(1, 0.9);
                s.setPosition(1267+3,42+5);
                window.draw(s);
            }
            if (Captured[0][4] != 0)
            {
                board_texture.loadFromFile("Rook-W.png");
                sf::Sprite s(board_texture);
                s.setScale(0.85, 0.85);
                s.setPosition(1000+10,183+10);
                window.draw(s);
            }
            if (Captured[0][5] != 0)
            {
                board_texture.loadFromFile("Lance-W.png");
                sf::Sprite s(board_texture);
                s.setScale(0.7, 0.5);
                s.setPosition(1109+20,183);
                window.draw(s);
            }
            if (Captured[0][6] != 0)
            {
                board_texture.loadFromFile("Knight-W.png");
                sf::Sprite s(board_texture);
                s.setScale(0.9, 0.9);
                s.setPosition(1224+3,183+5);
                window.draw(s);
            }



            /// Black


            if (Captured[1][0] != 0)
            {
                board_texture.loadFromFile("GG-B.png");
                sf::Sprite s(board_texture);
                s.setScale(0.7, 0.7);

                s.setPosition(929+5,770+5);
                window.draw(s);
            }
            if (Captured[1][1] != 0)
            {
                board_texture.loadFromFile("SG-B.png");
                sf::Sprite s(board_texture);
                s.scale(0.11, 0.11);
                s.setPosition(1041+10,770+10);
                window.draw(s);
            }
            if (Captured[1][2] != 0)
            {
                board_texture.loadFromFile("Pawn-B.png");
                sf::Sprite s(board_texture);
                s.setScale(0.85, 0.85);
                s.setPosition(1153+20,770+10);
                window.draw(s);
            }
            if (Captured[1][3] != 0)
            {
                board_texture.loadFromFile("Bishop-B.png");
                sf::Sprite s(board_texture);
                s.setScale(1, 0.9);
                s.setPosition(1267+3,770+5);
                window.draw(s);
            }
            if (Captured[1][4] != 0)
            {
                board_texture.loadFromFile("Rook-B.png");
                sf::Sprite s(board_texture);
                s.setScale(0.85, 0.85);
                s.setPosition(1000+15,615+12);
                window.draw(s);
            }
            if (Captured[1][5] != 0)
            {
                board_texture.loadFromFile("Lance-B.png");
                sf::Sprite s(board_texture);
                s.setScale(0.7, 0.5);
                s.setPosition(1109 + 20, 615);
                window.draw(s);
            }
            if (Captured[1][6] != 0)
            {
                sf::Texture t;
                t.loadFromFile("Knight-B.png");
                sf::Sprite s(t);
                s.setScale(0.9, 0.9);
                s.setPosition(1224+3, 615+5);
                window.draw(s);
            }
        }

        
}

void Board::PieceDroping()
{
    int col1 = Board::row1;
    int row1 = Board::col1;

    if (!turn)
    {
        if (col1 > 770 && col1 < 870)
        {
            if (row1 > 929 && row1 < 1029 && Captured[1][0]!=0)
            {
                pieceToDrop = 'G';
            }
            else if (row1 > 1041 && row1 < 1141 && Captured[1][1]!=0)
            {
                pieceToDrop = 'S';
            }
            else if (row1 > 1153 && row1 < 1253&& Captured[1][2]!=0)
            {
                pieceToDrop = 'P';
            }
            else if (row1 > 1267 && row1 < 1367 && Captured[1][3]!=0)
            {
                pieceToDrop = 'B';
            }
        }
        else if (col1 > 615 && col1 < 715)
        {
            if (row1 > 1000 && row1 < 1100 && Captured[1][4]!=0)
            {
                pieceToDrop = 'R';
            }
            else if (row1 > 1109 && row1 < 1209 && Captured[1][5]!=0)
            {
                pieceToDrop = 'L';
            }
            else if (row1 > 1224 && row1 < 1324 && Captured[1][6]!=0)
            {
                pieceToDrop = 'H';
            }
        }
    }
    else
    {
        if (col1 > 42 && col1 < 142)
        {
            if (row1 > 929 && row1 < 1029 && Captured[0][0]!=0)
            {
                pieceToDrop = 'g';
            }
            else if (row1 > 1041 && row1 < 1141&& Captured[0][1]!=0)
            {
                pieceToDrop = 's';
            }
            else if (row1 > 1153 && row1 < 1253 && Captured[0][2]!=0)
            {
                pieceToDrop = 'p';
            }
            else if (row1 > 1267 && row1 < 1367 && Captured[0][3]!=0)
            {
                pieceToDrop = 'b';
            }
        }
        else if (col1 > 183 && col1 < 283)
        {
            if (row1 > 1000 && row1 < 1100 && Captured[0][4]!=0)
            {
                pieceToDrop = 'r';
            }
            else if (row1 > 1109 && row1 < 1209 && Captured[0][5]!=0)
            {
                pieceToDrop = 'l';
            }
            else if (row1 > 1224 && row1 < 1324 && Captured[0][6]!=0)
            {
                pieceToDrop = 'h';
            }
        }
    }
}



void Board::select_src(bool& newGame,bool& isUndo,sf::RenderWindow& window)
{
    string src;
    bool valid1 = false;
    do
    {
        /*gotoRowCol(15, 0);
        cout << "Click the source." << endl;*/
        getRowColbyLeftClick(row1, col1,window);
        PieceDroping();
        if (row1 >= 245 && row1 <= 325 && col1 >= 1427 && col1 <= 1479)//
        {
            turn = 0;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    Captured[i][j] = 0;
                }
            }
            newGame = true;
            return;
        }
        else if (row1 >= 110 && row1 <= 169 && col1 >= 1422 && col1 <= 1481)
        {
            saveInFile("Load.txt");
            sf::Texture GS;
            GS.loadFromFile("GameSaved.jpg");
            sf::Sprite gs(GS);
            gs.setPosition(300, 300);
            window.display();
            window.draw(gs);
            window.display();
            Sleep(1000);
            DisplayBoard(window);
            window.display();
            continue;
        }
        else if (row1 >= 28 && row1 <= 86 && col1 >= 1422 && col1 <= 1481) 
        {
            window.close();
            exit(1);
        }
        else if (row1 >= 196 && row1 <= 245 && col1 >= 1426 && col1 <= 1476)
        {
            SetBoard("Undo.txt",true);
            isUndo = true;
            return;
        }
        if (pieceToDrop==NULL)
        {
            row1 /= 100;
            col1 /= 100;
            valid1 = IsValidSourceSelection(row1, col1);
            if (valid1 == 1)
            {
                Box[row1][col1]->highlight(window);
            }
        }
        else
        {
            break;
        }
        
    } while (!valid1);
}


void  Board::select_des(bool& newGame, bool& isUndo,sf::RenderWindow& window)
{
    string des;
    do
    {
        /*gotoRowCol(28, 0);
        cout << "click the destination." << endl;*/
        getRowColbyLeftClick(row2, col2, window);

        if (pieceToDrop!=NULL)
        {
            while (true)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    sf::Vector2i p = sf::Mouse::getPosition(window);
                    bool present = false;
                    col2 = p.x;
                    row2 = p.y;
                    row2 /= 100;
                    col2 /= 100;
                    if (Box[row2][col2]==nullptr)
                    {
                        if (pieceToDrop=='p')
                        {
                            for (int i = 0; i < 9; i++)
                            {
                                if (Box[i][col2]!=nullptr &&  Box[i][col2]->getName() == 'p' && !Box[i][col2]->isPromoted())
                                {
                                    present = true;
                                    break;
                                }
                            }
                            if (!present)
                            {
                                Box[row2][col2] = new Pawn(this, row2, col2, Ps[0]->getClr());
                                if (!check(!turn))
                                {
                                    //delete[]  Box[row2][col2];
                                    Box[row2][col2] = nullptr;
                                    return;
                                }

                                //delete[]  Box[row2][col2];
                                Box[row2][col2] = nullptr;
                            }
                        }
                        else if (pieceToDrop=='P')
                        {
                            for (int i = 0; i < 9; i++)
                            {
                                if (Box[i][col2] != nullptr && Box[i][col2]->getName() == 'P' && !Box[i][col2]->isPromoted())
                                {
                                    present = true;
                                    break;
                                }
                            }
                            if (!present)
                            {
                                return;
                            }
                        }
                        
                    }
                }
            }
        }

        if (row1 >= 245 && row1 <= 325 && col1 >= 1427 && col1 <= 1479)//
        {
            turn = 0;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    Captured[i][j] = 0;
                }
            }
            newGame = true;
            return;
        }
        else if (row1 >= 110 && row1 <= 169 && col1 >= 1422 && col1 <= 1481)
        {
            saveInFile("Load.txt");
            sf::Texture GS;
            GS.loadFromFile("GameSaved.jpg");
            sf::Sprite gs(GS);
            gs.setPosition(300, 300);
            window.display();
            window.draw(gs);
            window.display();
            Sleep(1000);
            DisplayBoard(window);
            window.display();
            continue;
        }
        else if (row1 >= 28 && row1 <= 86 && col1 >= 1422 && col1 <= 1481)
        {
            window.close();
            exit(1);
        }
        else if (row1 >= 196 && row1 <= 245 && col1 >= 1426 && col1 <= 1476)
        {
            SetBoard("Undo.txt", true);
            isUndo = true;
            return;
        }

        row2 /= 100;
        col2 /= 100;


    } while (!IsValidDestSelection(row2,col2));

    //unhighlight(board, row1, col1, turn);

}




bool Board::isLegalMove(int row1, int col1, int row2, int col2)
{
    return(Box[row1][col1]->IsLegal(row1,col1,row2,col2));

}

void Board::Findking(int& kr, int& kc,bool t)
{
    King* King_pointer;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {            
            if(Box[i][j]!=nullptr &&  Box[i][j]->MyPiece(t))
            {
                King_pointer = dynamic_cast<King*>(Box[i][j]);
                if (King_pointer != nullptr)
                {
                    kr = i;
                    kc = j;
                    return;
                }
            }
        }
    }
}


bool Board::check(bool t)
{
    int kr, kc;
    Findking(kr, kc,!t);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (Box[i][j]!=nullptr && Box[i][j]->MyPiece(t) && Box[i][j]->IsLegal(i, j, kr, kc))
            {
                return true;
            }
        }
    }
    return false;
}


bool Board::selfCheak(int row1,int col1,int row2,int col2)
{
    Piece* temp = Box[row2][col2];
    Box[row1][col1]->Move(row1, col1, row2, col2,true);
    bool c = check(!turn);
    Box[row2][col2]->Move(row2, col2, row1, col1,true);
    Box[row2][col2] = temp;
    return c;
}


bool Board::canImove()
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (Box[i][j] == nullptr)
            {
                continue;
            }
            else if (!Box[i][j]->MyPiece(turn))
            {
                continue;
            }

            for (int x = 0; x < 9; x++)
            {
                for (int y = 0; y < 9; y++)
                {
                    if ( (Box[x][y]==nullptr  || !Box[x][y]->MyPiece(turn)) && (isLegalMove(i, j, x, y)) && !selfCheak(i, j, x, y))
                    {
                        return true;
                    }
                }
            }
        }

    }
    return false;
}


void Board::pawnPromotion(sf::RenderWindow& window)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (Box[i][j] != nullptr && Box[i][j]->MyPiece(turn))
                Box[i][j]->Promotion(window);
        }
    }
}



void Board::saveInFile(string fn)
{
    ofstream Writer(fn);

    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            if (Box[r][c] == nullptr)
            {
                Writer << "-";
            }
            else
            {
                Writer << Box[r][c]->getName();
            }
        }
        Writer << endl;
    }
    Writer << Ps[0]->getName();
    Writer << endl;
    Writer << Ps[1]->getName();
    Writer << endl;
    Writer << turn;
    Writer << endl;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            Writer << Captured[i][j];
            Writer << " ";
        }
        Writer << endl;
    }

}


void Board::DropThePiece()
{

    if (pieceToDrop == 'P')
    {
        Box[row2][col2] = new Pawn(this, row2, col2, Ps[1]->getClr());
        Captured[1][2]--;
    }
    else if (pieceToDrop == 'B')
    {
        Box[row2][col2] = new Bishop(this, row2, col2, Ps[1]->getClr());
        Captured[1][3]--;
    }
    else if (pieceToDrop == 'R')
    {
        Captured[1][4]--;
        Box[row2][col2] = new Rook(this, row2, col2, Ps[1]->getClr());
    }
    else if (pieceToDrop == 'L')
    {
        Captured[1][5]--;
        Box[row2][col2] = new Lance(this, row2, col2, Ps[1]->getClr());
    }
    else if (pieceToDrop == 'H')
    {
        Captured[1][6]--;
        Box[row2][col2] = new Knight(this, row2, col2, Ps[1]->getClr());
    }
    else if (pieceToDrop == 'G')
    {
        Captured[1][0]--;
        Box[row2][col2] = new GoldenGeneral(this, row2, col2, Ps[1]->getClr());
    }
    else if (pieceToDrop == 'S')
    {
        Captured[1][1]--;
        Box[row2][col2] = new SilverGeneral(this, row2, col2, Ps[1]->getClr());
    }






    else if (pieceToDrop == 'p')
    {
        Captured[0][2]--;
        Box[row2][col2] = new Pawn(this, row2, col2, Ps[0]->getClr());
    }
    else if (pieceToDrop == 'b')
    {
        Captured[0][3]--;
        Box[row2][col2] = new Bishop(this, row2, col2, Ps[0]->getClr());
    }
    else if (pieceToDrop == 'r')
    {
        Captured[0][4]--;
        Box[row2][col2] = new Rook(this, row2, col2, Ps[0]->getClr());
    }
    else if (pieceToDrop == 'l')
    {
        Captured[0][5]--;
        Box[row2][col2] = new Lance(this, row2, col2, Ps[0]->getClr());
    }
    else if (pieceToDrop == 'h')
    {
        Captured[0][6]--;
        Box[row2][col2] = new Knight(this, row2, col2, Ps[0]->getClr());
    }
    else if (pieceToDrop == 'g')
    {
        Captured[0][0]--;
        Box[row2][col2] = new GoldenGeneral(this, row2, col2, Ps[0]->getClr());
    }
    else if (pieceToDrop == 's')
    {
        Captured[0][1]--;
        Box[row2][col2] = new SilverGeneral(this, row2, col2, Ps[0]->getClr());
    }



}




int Board::RunBoard(sf::RenderWindow& window)
{
    bool newGame = 0, isUndo = 0, legal = 1, check_h = 0;
    string turnName;

    do
    {
        DisplayBoard(window);
        window.display();
        do
        {
            isUndo = 0;
            window.display();
            turnName = Ps[turn]->getName();
            turnName.append("'S TURN");
            text.setString(turnName);
            text.setPosition(1000, 430);
            window.draw(text);
            window.display();
            select_src(newGame, isUndo, window);
            if (newGame == 1)
            {
                return true;
            }
            if (isUndo)
                break;
            select_des(newGame, isUndo, window);
            if (newGame == 1)
            {
                return true;
            }
            if (isUndo)
                break;
            if (pieceToDrop!=NULL)
            {
                break;
            }
        } while (!isLegalMove(row1, col1, row2, col2) || selfCheak(row1,col1,row2,col2));
        saveInFile("Undo.txt");
        if (isUndo)
            continue;
        {
            if (pieceToDrop!=NULL)
            {
                DropThePiece();
                pieceToDrop = NULL;
            }
            else
            {
                Box[row1][col1]->Move(row1, col1, row2, col2);
            }
            pawnPromotion(window);
            check_h = check(turn);
            if (check_h)
            {
                sf::Texture temp;
                if (!temp.loadFromFile("check-tag.jpg"))
                {
                    throw("Unable to load board img");
                }

                sf::Sprite s(temp);

                s.setPosition(900,400);
                DisplayBoard(window);
                window.draw(s);
                window.display();
                Sleep(2000);
            }


            turn = !turn;
        }
        if (check_h == 1)
        {
            if (!canImove())//  CheckMate
            {
                DisplayBoard(window);
                window.display();
                sf::Texture cm;
                cm.loadFromFile("General_Small_Box.jpg");
                sf::Sprite CM(cm);
                CM.setPosition(300, 300);
                window.draw(CM);
                text.setString("CHECKMATE");
                text.setPosition(380, 370);
                window.draw(text);
                text.setString(Ps[!turn]->getName());
                text.setPosition(380, 420);
                window.draw(text);
                text.setString("WON");
                text.setPosition(380, 470);
                window.draw(text);
                window.display();
                int t, T;
                getRowColbyLeftClick(t, T, window);
                return true;
                
            }
        }
        else
        {
            if (!canImove())  // Stale Mate
            {
                DisplayBoard(window);
                window.display();
                sf::Texture cm;
                cm.loadFromFile("General_Small_Box.jpg");
                sf::Sprite CM(cm);
                CM.setPosition(300, 300);
                window.draw(CM);
                text.setString("STALEMATE");
                text.setPosition(380, 370);
                window.draw(text);
                text.setString("IT's A TIE");
                text.setPosition(380, 420);
                window.draw(text);
                text.setString("BOTH PLAYED WELL");
                text.setPosition(380, 410);
                window.draw(text);
                window.display();
                int t, T;
                getRowColbyLeftClick(t, T, window);
                return true;
            }
        }
        

    } while (true);


    return false;
}

