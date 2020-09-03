#pragma once
#include"Sector.h"
class Board
{
	Sector sectors[8][8];
	POINT pt;
public:
	Board();
	virtual ~Board();
	void draw(HDC MemDC);
};