#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <winsock2.h>
using namespace std;

#define NOMESSAGE (-1)
#define BUFFERSIZE 256

extern ofstream logfile;

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

	string lastinmsg;

public:
	Connection();
	~Connection() {}

	bool isConnect() { return isconnect; }

	void Init();
	void Connect();
	void Close();

	void MessageSend(string &message);
	int MessageReceve();

	string getLastInputMessage() { return lastinmsg; }
};