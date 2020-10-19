#include "King.h"
King::King(): pt{ NULL }
{
	image.Load("Resources\\King.jpg");
}

King::King(char id) : pt{ NULL }, id{id}
{
	image.Load("Resources\\King.jpg");
}

King::~King()
{
	image.Destroy();
}

void King::draw(HDC MemDC) const
{
	image.Draw(MemDC, pt.x, pt.y, 80, 80);
}

void King::move(int x, int y)
{
	if (0 < x && x < SCREEN_WIDTH)
		pt.x = x;
	if (0 < y && y < SCREEN_HEIGHT)
		pt.y = y;
}