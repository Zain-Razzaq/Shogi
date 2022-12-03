#include "GoldenGeneral.h"


GoldenGeneral::GoldenGeneral(Board* b, int _cr, int _cc, Color cl)
{
	Piece::b = b;
	Piece::cr = _cr;
	Piece::cc = _cc;
	Piece::C = cl;

	if (C == W)
	{
		img = "GG-W.png";
		Name = 'g';
	}
	else
	{
		Name = 'G';
		img = "GG-B.png";
	}
}
void GoldenGeneral::print(sf::RenderWindow& window)
{
	sf::Texture temp;
	if (!temp.loadFromFile(img))
	{
		throw("Unable to load board img");
	}

	sf::Sprite s(temp);
	s.setScale(0.7, 0.7);

	s.setPosition((cc * 100) + 5, (cr * 100) + 5);
	window.draw(s);
}
bool GoldenGeneral::IsLegal(int row1, int col1, int row2, int col2)
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


void GoldenGeneral::Promotion(sf::RenderWindow& window)
{
	return;
}
