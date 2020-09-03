#include "Board.h"

Board::Board()
{
	Color c = Color::WHITE;
	pt = { 0,0 };
	for (int i = 0; i < 8; ++i) {
		c = Color((int)c + 1 % 2);
		for (int j = 0; j < 8; ++j) {
			sectors[i][j] = Sector(Color((int)c + 1 % 2), POINT{ pt.x + 20 * i, pt.y + 20 * j });
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