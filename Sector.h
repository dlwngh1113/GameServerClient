#pragma once
#include<atlimage.h>

#define SECTORSIZE 80

enum class Color {
	BLACK,
	WHITE
};

class Sector
{
	//Sector Image
	CImage image;
	//Sector Color
	Color color = Color::BLACK;
	//position
	POINT pt{ 0 };
public:
	Sector() = default;
	Sector(Color color, POINT pt);
	virtual ~Sector();
	void draw(HDC MemDC);
};