#include "GameFramework.h"

ClientInfo GameFramework::clientInfo;
King** GameFramework::players{ new King * [MAX_USERS] };

GameFramework::GameFramework() :board{ new Board }
{
	for (int i = 0; i < MAX_USERS; ++i)
		players[i] = NULL;
	players[0] = new King{};
}

GameFramework::~GameFramework()
{
	if (board)
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
			strcpy_s(clientInfo.sendBuffer, std::to_string(VK_LEFT).c_str());
			clientInfo.sendWsabuf.buf = clientInfo.sendBuffer;
			clientInfo.sendWsabuf.len = strlen(clientInfo.sendBuffer);
			DWORD num_sent;
			WSASend(clientInfo.socket, &clientInfo.sendWsabuf, 1, &num_sent, 0, &clientInfo.sendOver, Send_Complete);
		}
		break;
		case VK_RIGHT:
		{
			strcpy_s(clientInfo.sendBuffer, std::to_string(VK_RIGHT).c_str());
			clientInfo.sendWsabuf.buf = clientInfo.sendBuffer;
			clientInfo.sendWsabuf.len = strlen(clientInfo.sendBuffer);
			DWORD num_sent;
			WSASend(clientInfo.socket, &clientInfo.sendWsabuf, 1, &num_sent, 0, &clientInfo.sendOver, Send_Complete);
		}
		break;
		case VK_UP:
		{
			strcpy_s(clientInfo.sendBuffer, std::to_string(VK_UP).c_str());
			clientInfo.sendWsabuf.buf = clientInfo.sendBuffer;
			clientInfo.sendWsabuf.len = strlen(clientInfo.sendBuffer);
			DWORD num_sent;
			WSASend(clientInfo.socket, &clientInfo.sendWsabuf, 1, &num_sent, 0, &clientInfo.sendOver, Send_Complete);
		}
		break;
		case VK_DOWN:
		{
			strcpy_s(clientInfo.sendBuffer, std::to_string(VK_DOWN).c_str());
			clientInfo.sendWsabuf.buf = clientInfo.sendBuffer;
			clientInfo.sendWsabuf.len = strlen(clientInfo.sendBuffer);
			DWORD num_sent;
			WSASend(clientInfo.socket, &clientInfo.sendWsabuf, 1, &num_sent, 0, &clientInfo.sendOver, Send_Complete);
		}
		break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;
	}
}

void GameFramework::Draw(HDC hdc)
{
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	HDC MemDC = CreateCompatibleDC(hdc);

	SelectObject(MemDC, hBitmap);
	board->draw(MemDC);
	for (int i = 0; i < MAX_USERS; ++i)
		if (players[i])
			players[i]->draw(MemDC);
	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, MemDC, 0, 0, SRCCOPY);
}

void GameFramework::SetServerAddr(CHAR* addr)
{
	WSAStartup(MAKEWORD(2, 2), &clientInfo.wsaData);
	clientInfo.socket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&clientInfo.serverAddr, 0, sizeof(clientInfo.serverAddr));
	clientInfo.serverAddr.sin_family = AF_INET;
	clientInfo.serverAddr.sin_port = htons(PORT);
	int a = inet_pton(AF_INET, addr, &clientInfo.serverAddr.sin_addr);

	ZeroMemory(&clientInfo.sendOver, sizeof(clientInfo.sendOver));
	ZeroMemory(&clientInfo.recvOver, sizeof(clientInfo.recvOver));
	clientInfo.recvWsabuf.buf = clientInfo.recvBuffer;
	WSAConnect(clientInfo.socket, (sockaddr*)&clientInfo.serverAddr, sizeof(clientInfo.serverAddr), NULL, NULL, NULL, NULL);
}

void GameFramework::PlayerMove()
{
	std::string s = clientInfo.recvWsabuf.buf;
	int idx, x, y;
	std::stringstream ss;
	ss.str(s);
	while (ss >> idx >> x >> y) {
		if (!players[idx])
			players[idx] = new King{};
		players[idx]->move(x, y);
	}
}

void GameFramework::Update()
{
	SleepEx(10, TRUE);
	DWORD flag = NULL;
	ZeroMemory(&clientInfo.recvOver, sizeof(clientInfo.recvOver));
	WSARecv(GameFramework::clientInfo.socket, &clientInfo.recvWsabuf, 1, NULL, &flag, &clientInfo.recvOver, Recv_Complete);
}

void CALLBACK Send_Complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flag)
{
	if (bytes > 0) {
	}
	else {
		printf("Client Closed\n");
		closesocket(GameFramework::clientInfo.socket);
		return;
	}

	ZeroMemory(&GameFramework::clientInfo.recvOver, sizeof(GameFramework::clientInfo.recvOver));
	GameFramework::clientInfo.recvWsabuf.len = BUF_SIZE;
	WSARecv(GameFramework::clientInfo.socket, &GameFramework::clientInfo.recvWsabuf, 1, NULL, &flag, &GameFramework::clientInfo.recvOver, Recv_Complete);
}

void CALLBACK Recv_Complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flag)
{
	if (bytes > 0) {
		DWORD dwByte = NULL;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WriteFile(hConsole, GameFramework::clientInfo.recvWsabuf.buf, GameFramework::clientInfo.recvWsabuf.len, &dwByte, NULL);
		GameFramework::PlayerMove();
	}
	else {
		ZeroMemory(&GameFramework::clientInfo.recvOver, sizeof(GameFramework::clientInfo.recvOver));
		WSARecv(GameFramework::clientInfo.socket, &GameFramework::clientInfo.recvWsabuf, 1, NULL, &flag, &GameFramework::clientInfo.recvOver, Recv_Complete);
		return;
	}
	GameFramework::clientInfo.sendWsabuf.len = bytes;
	ZeroMemory(&GameFramework::clientInfo.sendOver, sizeof(GameFramework::clientInfo.sendOver));
}