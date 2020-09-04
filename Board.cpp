#include "Board.h"

Board::Board():pt{ NULL }
{
	Color c = Color::WHITE;
	for (int i = 0; i < 8; ++i) {
		c = static_cast<Color>(((int)c + 1) % 2);
		for (int j = 0; j < 8; ++j) {
			sectors[i][j] = Sector(c, POINT{ pt.x + SECTORSIZE * i, pt.y + SECTORSIZE * j });
			c = static_cast<Color>(((int)c + 1) % 2);
		}
	}
}

Board::~Board()
{

}

void Board::draw(HDC MemDC)
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			sectors[i][j].draw(MemDC);
}