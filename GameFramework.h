#pragma once
#include"framework.h"
#include"Board.h"
#include"King.h"
#include"ClientInfo.h"

class GameFramework
{
	static King** players;
	Board* board = NULL;
public:
	static ClientInfo clientInfo;
	GameFramework();
	virtual ~GameFramework();
	void KeyInputManager(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetServerAddr(CHAR* addr);
	void Draw(HDC MemDC)const;
	static void PlayerMove();
};

void CALLBACK Send_Complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flag);
void CALLBACK Recv_Complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flag);