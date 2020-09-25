#pragma once
#include"framework.h"

class ClientInfo {
public:
	char messageBuffer[BUF_SIZE + 1];
	WSADATA wsaData;
	WSABUF wsaBuf;

	SOCKET socket;
	SOCKADDR_IN serverAddr;
	WSAOVERLAPPED over;
};