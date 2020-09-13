#include "King.h"
King::King(): pt{ NULL }
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

void King::move(int dx, int dy)
{
	if(pt.x + dx >= 0 && pt.x + dx < SCREEN_WIDTH)
		pt.x += dx;
	if (pt.y + dy >= 0 && pt.y + dy < SCREEN_HEIGHT)
		pt.y += dy;
}