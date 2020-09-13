#pragma once
#include"framework.h"
#include<atlimage.h>
class King
{
	CImage image;
	POINT pt;
public:
	King();
	virtual ~King();
	void draw(HDC MemDC)const;
	void move(int dx, int dy);
};