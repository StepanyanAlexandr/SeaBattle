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
	static SOCKET listener;
	
	WSADATA wsadata;
	WORD libversion;

	SOCKADDR_IN inaddr;
	SOCKET connection;
	
	int inaddrsize;
	bool isconnect;
public:
	Connection();
	~Connection() {}

	bool isConnect() { return isconnect; }

	void Init();
	void Connect();
	void Close();

	void MessageSend(char *message) { send(connection, message, BUFFERSIZE, 0); }
	void MessageReceve(char *message) { recv(connection, message, BUFFERSIZE, 0); }
};