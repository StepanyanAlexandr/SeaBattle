#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include <iostream>
#include <winsock2.h>
using namespace std;

#define WSASTARTUPFAILURE (-2)
#define CONNECTIONSUCCESSFULL (1)

#define BUFFERSIZE 256

class Connection
{
private:
	WSADATA wsadata;
	WORD libversion;

	SOCKADDR_IN serveraddr;
	SOCKET server;
	int serveraddrsize;

public:
	Connection();
	~Connection() {}

	bool Init(const char *address);
	bool Connect();
	void Close();

	void MessageSend(char *message) { send(server, message, BUFFERSIZE, 0); }
	void MessageReceve(char *message) { recv(server, message, BUFFERSIZE, 0); }
};