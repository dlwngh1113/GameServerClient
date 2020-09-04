#pragma once
#include<atlimage.h>
class King
{
	CImage image;
public:
	POINT pt;
	King();
	virtual ~King();
	void draw(HDC MemDC)const;
};