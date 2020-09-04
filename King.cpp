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