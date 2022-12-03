#include"Shogi.h"
#include "Header.h"
#include "Board.h"



Shogi::Shogi()
{
    P = new string[2];
}

string fromKtoS(const sf::Keyboard::Key& k) {
    string ret;
    switch (k) {

    case 97:

        ret = "A";
        break;
    case 98:

        ret = "B";
        break;
    case 99:

        ret = "C";
        break;
    case 100:

        ret = "D";
        break;
    case 101:

        ret = "E";
        break;
    case 102:

        ret = "F";
        break;
    case 103:

        ret = "G";
        break;
    case 104:

        ret = "H";
        break;
    case 105:

        ret = "I";
        break;
    case 106:

        ret = "J";
        break;
    case 107:

        ret = "K";
        break;
    case 108:

        ret = "L";
        break;
    case 109:

        ret = "M";
        break;
    case 110:

        ret = "N";
        break;
    case 111:

        ret = "O";
        break;
    case 112:

        ret = "P";
        break;
    case 113:

        ret = "Q";
        break;
    case 114:

        ret = "R";
        break;
    case 115:

        ret = "S";
        break;
    case 116:

        ret = "T";
        break;
    case 117:

        ret = "U";
        break;
    case 118:

        ret = "V";
        break;
    case 119:

        ret = "W";
        break;
    case 120:

        ret = "X";
        break;
    case 121:

        ret = "Y";
        break;
    case 122:

        ret = "Z";
        break;

    default:
        ret = "";
        break;
    }
    return ret;
}


void Shogi::EnterPlayers(sf::RenderWindow& window)
{

    text.setPosition(960, 680);
    text.setCharacterSize(50);
    window.clear();
    sf::Texture te;
    if (!te.loadFromFile("Welcom4.jpg"))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s1(te);
    window.draw(s1);
    window.display();

    sf::String playerInput;
    std::string s, t;
    sf::Event event = {};
    bool entered = false;

    while (window.isOpen() && !entered) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.key.code == 13)
                {
                    entered = true;
                    break;
                }
                t = fromKtoS(event.key.code);
                s.append(t);
                text.setString(s);
                window.clear();
                window.draw(s1);
                window.draw(text);
                window.display();

            }
        }
    }


    P[0] = s;
    //P[0] = s;

    if (!te.loadFromFile("Welcom5.jpg"))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s2(te);

    std::string S;

    window.clear();
    window.draw(s2);
    window.display();
    text.setPosition(960, 680);

    entered = false;

    while (window.isOpen() && !entered) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.key.code == 13)
                {
                    entered = true;
                    break;
                }
                t = fromKtoS(event.key.code);
                S.append(t);
                text.setString(S);
                window.clear();
                window.draw(s2);
                window.draw(text);
                window.display();

            }
        }
    }


    P[1] = S;

}


void Shogi::RunShogi()
{
	

	sf::RenderWindow window(
		sf::VideoMode(1500, 900),
		"Shogi-ZR Studios");
	font.loadFromFile("font.otf");
	text.setFont(font);

    window.setPosition(sf::Vector2i(0,0));

    sf::Texture te;
    if (!te.loadFromFile("Welcom1.jpg"))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s(te);
    window.draw(s);
    window.display();
    sleep(2000);
    

    if (!te.loadFromFile("Welcom1.5.jpg"))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s1(te);
    window.draw(s1);
    window.display();
    sleep(2000);

    if (!te.loadFromFile("Welcom2.jpg"))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s2(te);
    window.clear();
    window.draw(s2);
    window.display();
    sleep(3000);
    window.clear();


    if (!te.loadFromFile("Welcom3.jpg"))
    {
        throw("Unable to load board img");
    }

    sf::Sprite s3(te);
    window.clear();
    window.draw(s3);
    window.display();
    window.clear();
    int r, c;
    bool newGame = false;
    Board B;
    while (true)
    {
        getRowColbyLeftClick(r, c, window);
        if (r >= 483 && c >= 994 && r <= 591 && c <= 1411) //new game
        {
            do
            {
                EnterPlayers(window);
                B.SetBoard("newgame.txt", false, P[0], P[1]);
                B.saveInFile("Load.txt");
                newGame = B.RunBoard(window);
            } while (newGame);
            break;
        }
        else if (r >= 623 && c >= 994 && r <= 734 && c <= 1411)  //load 
        {
            do
            {
                if (newGame)
                {
                    EnterPlayers(window);
                    B.SetBoard("newgame.txt", false, P[0], P[1]);
                    B.saveInFile("Load.txt");
                    newGame = B.RunBoard(window);
                }
                B.SetBoard("Load.txt", true);
                newGame = B.RunBoard(window);
            } while (newGame);

            
            break;
        }
        else if (r >= 760 && c >= 994 && r <= 871 && c <= 1411)  //exit
        {
            window.close();
            exit(1);
        }
    }


    
}




