#include "SilverGeneral.h"

SilverGeneral::SilverGeneral(Board* b, int _cr, int _cc, Color cl,bool pm)
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
			Name = '%';
			img = "SG-WP.png";
		}
		else if (C == B )
		{
			Name = '_';
			img = "SG-BP.png";
		}
	}
	else
	{
		if (C == W)
		{
			img = "SG-W.png";
			Name = 's';
		}
		else
		{
			img = "SG-B.png";
			Name = 'S';
		}
	}
}
void SilverGeneral::print(sf::RenderWindow& window)
{
	sf::Texture temp;
	if (!temp.loadFromFile(img))
	{
		throw("Unable to load board img");
	}

	sf::Sprite s(temp);
	s.scale(0.11, 0.11);
	s.setPosition((cc * 100) + 10, (cr * 100) + 10);
	

	window.draw(s);
}
bool SilverGeneral::IsLegal(int row1, int col1, int row2, int col2)
{
	int Dr, Dc;
	Dr = (row2 - row1);
	Dc = (col2 - col1);


	if (promoted)
	{
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



	if (Dr == 0)
		return false;

	if (C == W)
	{
		if (Dr == 1 && Dc == 0)
			return false;
	}
	else if (C == B)
	{
		if (Dr == -1 && Dc == 0)
			return false;
	}

	Dr = abs(Dr);
	Dc = abs(Dc);

	return(((Dr == 1 && Dc == 0) || (Dr == 0 && Dc == 1) || (Dr == 1 && Dc == 1)));
}

void SilverGeneral::Promotion(sf::RenderWindow& window)
{

	if (!promoted)
	{

		if (C == W && cr < 3)
		{
			if (AskForPromotion(window))
			{
				Name = '%';
				img = "SG-WP.png";
				promoted = true;
			}

		}
		else if (C == B && cr > 5)
		{
			if (AskForPromotion(window))
			{
				Name = '_';
				img = "SG-BP.png";
				promoted = true;
			}

		}
	}
}