#include "Board.h"

Board::Board():pt{ NULL }
{
	Color c = Color::WHITE;
	sectors.resize(8);
	for (int i = 0; i < 8; ++i) {
		sectors[i].reserve(8);
		c = static_cast<Color>(((int)c + 1) % 2);
		for (int j = 0; j < 8; ++j) {
			sectors[i].push_back(new Sector(c, POINT{ pt.x + SECTORSIZE * i, pt.y + SECTORSIZE * j }));
			c = static_cast<Color>(((int)c + 1) % 2);
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < 8; ++i)
		sectors[i].clear();
	sectors.clear();
}

void Board::draw(HDC MemDC) const
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			sectors[i][j]->draw(MemDC);
}