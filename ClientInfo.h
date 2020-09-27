#pragma once
#include"framework.h"

class ClientInfo {
public:
	char recvBuffer[BUF_SIZE + 1] = { NULL };
	char sendBuffer[BUF_SIZE + 1] = { NULL };
	WSADATA wsaData;
	WSABUF sendWsabuf;
	WSABUF recvWsabuf;

	SOCKET socket;
	SOCKADDR_IN serverAddr;
	WSAOVERLAPPED recvOver;
	WSAOVERLAPPED sendOver;
};