#include "Knight.h"

Knight::Knight(Board* b, int _cr, int _cc, Color cl,bool pm)
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
			Name = '$';
			img = "Knight-WP.png";
		}
		else if (C == B)
		{
			Name = ')';
			img = "Knight-BP.png";
		}
	}
	else
	{
		if (C == W)
		{
			img = "Knight-W.png";
			Name = 'h';
		}
		else
		{
			img = "Knight-B.png";
			Name = 'H';
		}
	}
}
void Knight::print(sf::RenderWindow& window)
{
	sf::Texture temp;
	if (!temp.loadFromFile(img))
	{
		throw("Unable to load board img");
	}

	sf::Sprite s(temp);
	s.setScale(0.9, 0.9);

	s.setPosition((cc * 100) + 5, (cr * 100) + 3);
	window.draw(s);


}
bool Knight::IsLegal(int row1, int col1, int row2, int col2)
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


	Dr = (row2 - row1);
	Dc = abs(col2 - col1);
	if (C == W && Dr != -2)
		return false;
	else if (C == B && Dr != 2)
		return false;
	return(Dc == 1);

}


void Knight::Promotion(sf::RenderWindow& window)
{

	if (!promoted)
	{
		if (C == W && cr == 2)
		{
			if (first)
			{
				bool p;
				p = AskForPromotion(window);
				if (p)
				{
					Name = '$';
					img = "Knight-WP.png";
					promoted = true;
				}
				first = false;
			}
		}
		else if (C == W && cr < 2)
		{
			Name = '$';
			img = "Knight-WP.png";
			promoted = true;
		}
		else if (C == B && cr == 6)
		{
			if (first)
			{
				bool p;
				p = AskForPromotion(window);
				if (p)
				{
					Name = ')';
					img = "Knight-BP.png";
					promoted = true;
				}
				first = false;
			}
		}
		else if (C == B && cr > 6)
		{
			Name = ')';
			img = "Knight-BP.png";
			promoted = true;
		}

	}
}
