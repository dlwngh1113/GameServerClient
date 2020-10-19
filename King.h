#pragma once
#include"framework.h"
#include<atlimage.h>
class King
{
	CImage image;
	char id;
	POINT pt;
public:
	King();
	King(char id);
	virtual ~King();
	void draw(HDC MemDC)const;
	void move(int dx, int dy);
};