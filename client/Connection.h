#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include <iostream>
#include <winsock2.h>
using namespace std;

#define NOMESSAGE (-1)
#define BUFFERSIZE 256

#define SERVERADDRESS "192.168.0.106"

class Connection
{
private:
	WSADATA wsadata;
	WORD libversion;

	SOCKADDR_IN serveraddr;
	SOCKET server;
	
	int serveraddrsize;
	bool isconnect;

	string lastinmsg;
public:
	Connection();
	~Connection() {}

	bool isConnect() { return isconnect; }

	void Init();
	void Connect();
	void Close();

	void MessageSend(string &message) { send(server, message.c_str(), BUFFERSIZE, 0); }
	int MessageReceve();

	string getLastInputMessage() { return lastinmsg; }
};