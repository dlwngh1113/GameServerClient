#include "Sector.h"

Sector::Sector(Color color, POINT pt) :color{ color },pt{ pt }
{
	switch (color)
	{
	case Color::BLACK:
		image.Load("Resources\\blackSector.png");
		break;
	case Color::WHITE:
		image.Load("Resources\\whiteSector.png");
		break;
	}
}

Sector::~Sector()
{
	image.Destroy();
}

void Sector::draw(HDC MemDC)
{
	image.Draw(MemDC, pt.x, pt.y, SECTORSIZE, SECTORSIZE);
}