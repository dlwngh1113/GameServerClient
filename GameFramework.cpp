#include "GameFramework.h"

GameFramework::GameFramework():board{new Board}, player{new King}
{
	
}

GameFramework::~GameFramework()
{
	if(board)
		delete board;
	if(player)
		delete player;
	WSACleanup();
}

void GameFramework::KeyInputManager(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN: 
		{
		char buff[BUF_SIZE + 1];
		WSABUF wsaBuf;
			switch (wParam)
			{
			case VK_LEFT: 
			{
				strcpy_s(buff, BUF_SIZE + 1, "VK_LEFT");
				wsaBuf.buf = buff;
				wsaBuf.len = static_cast<ULONG>(strlen("VK_LEFT") + 1);
				DWORD num_sent;
				WSASend(serverSocket, &wsaBuf, 1, &num_sent, 0, NULL, NULL);
				DWORD num_recv;
				DWORD flag = 0;
				wsaBuf.len = BUF_SIZE;
				WSARecv(serverSocket, &wsaBuf, 1, &num_recv, &flag, NULL, NULL);
				player->move(atoi(wsaBuf.buf), 0);
			}
				break;
			case VK_RIGHT:
			{
				strcpy_s(buff, BUF_SIZE + 1, "VK_RIGHT");
				wsaBuf.buf = buff;
				wsaBuf.len = static_cast<ULONG>(strlen("VK_RIGHT") + 1);
				DWORD num_sent;
				WSASend(serverSocket, &wsaBuf, 1, &num_sent, 0, NULL, NULL);
				DWORD num_recv;
				DWORD flag = 0;
				wsaBuf.len = BUF_SIZE;
				WSARecv(serverSocket, &wsaBuf, 1, &num_recv, &flag, NULL, NULL);
				player->move(atoi(wsaBuf.buf), 0);
			}
				break;
			case VK_UP:
			{
				strcpy_s(buff, BUF_SIZE + 1, "VK_UP");
				wsaBuf.buf = buff;
				wsaBuf.len = static_cast<ULONG>(strlen("VK_UP") + 1);
				DWORD num_sent;
				WSASend(serverSocket, &wsaBuf, 1, &num_sent, 0, NULL, NULL);
				DWORD num_recv;
				DWORD flag = 0;
				wsaBuf.len = BUF_SIZE;
				WSARecv(serverSocket, &wsaBuf, 1, &num_recv, &flag, NULL, NULL);
				player->move(0, atoi(wsaBuf.buf));
			}
				break;
			case VK_DOWN:
			{
				strcpy_s(buff, BUF_SIZE + 1, "VK_DOWN");
				wsaBuf.buf = buff;
				wsaBuf.len = static_cast<ULONG>(strlen("VK_DOWN") + 1);
				DWORD num_sent;
				WSASend(serverSocket, &wsaBuf, 1, &num_sent, 0, NULL, NULL);
				DWORD num_recv;
				DWORD flag = 0;
				wsaBuf.len = BUF_SIZE;
				WSARecv(serverSocket, &wsaBuf, 1, &num_recv, &flag, NULL, NULL);
				player->move(0, atoi(wsaBuf.buf));
			}
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

void GameFramework::SetServerAddr(CHAR* addr)
{
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	serverSocket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	int a = inet_pton(AF_INET, addr, &serverAddr.sin_addr);
	WSAConnect(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr), NULL, NULL, NULL, NULL);
}