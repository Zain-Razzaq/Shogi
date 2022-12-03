#include "Lance.h"


Lance::Lance(Board* b, int _cr, int _cc, Color cl,bool pm) :Piece(b,_cr,_cc,cl)
{
	Piece::promoted = pm;
	if (promoted)
	{
		if (C == W )
		{
			Name = '#';
			img = "Lance-WP.png";
		}
		else if (C == B )
		{
			Name = '(';
			img = "Lance-BP.png";
		}
	}
	else
	{
		if (C == W)
		{
			img = "Lance-W.png";
			Name = 'l';
		}
		else
		{
			img = "Lance-B.png";
			Name = 'L';
		}
	}
}


void Lance::print(sf::RenderWindow& window)
{
	sf::Texture temp;
	if (!temp.loadFromFile(img))
	{
		throw("Unable to load board img");
	}

	sf::Sprite s(temp);
	s.setScale(0.7, 0.5);
	s.setPosition((cc * 100)+20, (cr * 100) );
	window.draw(s);
}
bool Lance::IsLegal(int row1, int col1, int row2, int col2)
{

	if (promoted)
	{
		int Dr, Dc;
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





	int Dr = (row2 - row1);
	if (C == W && Dr >= 0)
		return false;
	else if (C == B && Dr <= 0)
		return false;
	return((IsVerMove(row2, col2) && IsVerClear(row2, col2)));
}


void Lance::Promotion(sf::RenderWindow& window)
{

	if (!promoted)
	{
		if (C == W && (cr == 2 || cr == 1))
		{
			if (first)
			{
				bool p;
				p = AskForPromotion(window);
				if (p)
				{
					Name = '#';
					img = "Lance-WP.png";
					promoted = true;
				}
				first = false;
			}
		}
		else if (C == W && cr == 0)
		{
			Name = '#';
			img = "Lance-WP.png";
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
					Name = '(';
					img = "Lance-BP.png";
					promoted = true;
				}
				first = false;
			}
		}
		else if (C == B && cr == 8)
		{
			Name = '(';
			img = "Lance-BP.png";
			promoted = true;
		}

	}
}
