#pragma once
#include"framework.h"
#include"Board.h"
#include"King.h"

class GameFramework
{
	Board* board = NULL;
	King* player = NULL;
public:
	GameFramework();
	virtual ~GameFramework();
	void KeyInputManager(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void draw(HDC MemDC)const;
};

