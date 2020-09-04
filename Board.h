#pragma once
#include<vector>
#include"Sector.h"
class Board
{
	std::vector<std::vector<Sector*>> sectors;
	POINT pt;
public:
	Board();
	virtual ~Board();
	void draw(HDC MemDC);
};