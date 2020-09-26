#include "GameFramework.h"

ClientInfo GameFramework::clientInfo;
King** GameFramework::players{ new King * [MAX_USERS] };

GameFramework::GameFramework():board{new Board}
{
	for (int i = 0; i < MAX_USERS; ++i)
		players[i] = NULL;
	players[0] = new King{};
}

GameFramework::~GameFramework()
{
	if(board)
		delete board;
	for (int i = 0; i < MAX_USERS; ++i)
		if (players[i])
			delete players[i];
	delete[] players;
	WSACleanup();
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
			{
				strcpy_s(clientInfo.messageBuffer, BUF_SIZE + 1, "VK_LEFT");
				clientInfo.wsaBuf.buf = clientInfo.messageBuffer;
				clientInfo.wsaBuf.len = strlen("VK_LEFT");
				DWORD num_sent;
				WSASend(clientInfo.socket, &clientInfo.wsaBuf, 1, &num_sent, 0, &clientInfo.over, Send_Complete);
			}
				break;
			case VK_RIGHT:
			{
				strcpy_s(clientInfo.messageBuffer, BUF_SIZE + 1, "VK_RIGHT");
				clientInfo.wsaBuf.buf = clientInfo.messageBuffer;
				clientInfo.wsaBuf.len = strlen("VK_RIGHT");
				DWORD num_sent;
				WSASend(clientInfo.socket, &clientInfo.wsaBuf, 1, &num_sent, 0, &clientInfo.over, Send_Complete);
			}
				break;
			case VK_UP:
			{
				strcpy_s(clientInfo.messageBuffer, BUF_SIZE + 1, "VK_UP");
				clientInfo.wsaBuf.buf = clientInfo.messageBuffer;
				clientInfo.wsaBuf.len = strlen("VK_UP");
				DWORD num_sent;
				WSASend(clientInfo.socket, &clientInfo.wsaBuf, 1, &num_sent, 0, &clientInfo.over, Send_Complete);
			}
				break;
			case VK_DOWN:
			{
				strcpy_s(clientInfo.messageBuffer, BUF_SIZE + 1, "VK_DOWN");
				clientInfo.wsaBuf.buf = clientInfo.messageBuffer;
				clientInfo.wsaBuf.len = strlen("VK_DOWN");
				DWORD num_sent;
				WSASend(clientInfo.socket, &clientInfo.wsaBuf, 1, &num_sent, 0, &clientInfo.over, Send_Complete);
			}
				break;
			}
	}
	break;
	}
}

void GameFramework::Draw(HDC hdc) const
{
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	HDC MemDC = CreateCompatibleDC(hdc);

	SelectObject(MemDC, hBitmap);
	board->draw(MemDC);
	for (int i=0;i<MAX_USERS;++i)
		if(players[i])
			players[i]->draw(MemDC);
	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, MemDC, 0, 0, SRCCOPY);
}

void GameFramework::SetServerAddr(CHAR* addr)
{
	WSAStartup(MAKEWORD(2, 0), &clientInfo.wsaData);
	clientInfo.socket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&clientInfo.serverAddr, 0, sizeof(clientInfo.serverAddr));
	clientInfo.serverAddr.sin_family = AF_INET;
	clientInfo.serverAddr.sin_port = htons(PORT);
	int a = inet_pton(AF_INET, addr, &clientInfo.serverAddr.sin_addr);

	ZeroMemory(&clientInfo.over, sizeof(clientInfo.over));
	WSAConnect(clientInfo.socket, (sockaddr*)&clientInfo.serverAddr, sizeof(clientInfo.serverAddr), NULL, NULL, NULL, NULL);
}

void GameFramework::PlayerMove()
{
	std::string s = clientInfo.messageBuffer;
	int idx, x, y;
	std::stringstream ss;
	ss.str(s);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwByte(0);
	WriteFile(hConsole, s.c_str(), s.size(), &dwByte, NULL);
	while (ss >> idx >> x >> y) {
		if (!players[idx])
			players[idx] = new King{};
		players[idx]->move(x, y);
	}
}

void CALLBACK Send_Complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flag)
{
	if (bytes > 0) {
		printf("TRACE - Send Message : %s(%d bytes)\n", GameFramework::clientInfo.messageBuffer, bytes);
	}
	else {
		printf("Client Closed\n");
		closesocket(GameFramework::clientInfo.socket);
		return;
	}

	GameFramework::clientInfo.wsaBuf.len = BUF_SIZE;
	ZeroMemory(over, sizeof(*over));
	int ret = WSARecv(GameFramework::clientInfo.socket, &GameFramework::clientInfo.wsaBuf, 1, NULL, &flag, over, Recv_Complete);
}

void CALLBACK Recv_Complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flag)
{
	if (bytes > 0) {
		GameFramework::clientInfo.messageBuffer[bytes] = NULL;
		GameFramework::PlayerMove();
		printf("TRACE - Send Message : %s(%d bytes)\n", GameFramework::clientInfo.messageBuffer, bytes);
	}
	else {
		printf("Client Connection Closed\n");
		closesocket(GameFramework::clientInfo.socket);
		return;
	}
	GameFramework::clientInfo.wsaBuf.len = bytes;
	ZeroMemory(over, sizeof(*over));
	WSASend(GameFramework::clientInfo.socket, &GameFramework::clientInfo.wsaBuf, 1, NULL, 0, &GameFramework::clientInfo.over, Send_Complete);
}