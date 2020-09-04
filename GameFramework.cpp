#include "GameFramework.h"

GameFramework::GameFramework():board{new Board}, player{new King}
{

}

GameFramework::~GameFramework()
{
	delete board;
	delete player;
}

void GameFramework::KeyInputManager(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN: 
		{
			switch (wParam)
			{
			case VK_LEFT:
				if (player->pt.x > 0)
					player->pt.x -= SECTORSIZE;
				break;
			case VK_RIGHT:
				if (player->pt.x < SCREEN_WIDTH - SECTORSIZE)
					player->pt.x += SECTORSIZE;
				break;
			case VK_UP:
				if (player->pt.y > 0)
					player->pt.y -= SECTORSIZE;
				break;
			case VK_DOWN:
				if (player->pt.y < SCREEN_HEIGHT - SECTORSIZE)
					player->pt.y += SECTORSIZE;
				break;
			}
		}
	break;
	}
}

void GameFramework::draw(HDC hdc) const
{
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	HDC MemDC = CreateCompatibleDC(hdc);

	SelectObject(MemDC, hBitmap);
	board->draw(MemDC);
	player->draw(MemDC);
	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, MemDC, 0, 0, SRCCOPY);
}