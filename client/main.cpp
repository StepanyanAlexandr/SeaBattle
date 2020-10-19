#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include <iostream>
#include <winsock2.h>

using namespace std;

int main(int argc, char *argv[])
{
	WSAData wsadata;
	WORD libversion = MAKEWORD(2, 2);
	if (WSAStartup(libversion, &wsadata))
	{
		cout << "Error: Lib winsock2.h was not loaded" << endl;
		return 1;
	}

	SOCKADDR_IN inaddr;
	int inaddrsize = sizeof(inaddr);
	inaddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.106");
	inaddr.sin_port = htons(1600);
	inaddr.sin_family = AF_INET;

	SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connection == SOCKET_ERROR)
	{
		cout << "Error: socket was not created" << endl;
		return 2;
	}
	if (connect(connection, (SOCKADDR*)&inaddr, inaddrsize))
	{
		cout << "Error: unable to connect to server" << endl;
		return 3;
	}
	cout << "Connection succesfull" << endl;
	
	int bufsize = 256;
	char buffer[256];
	recv(connection, buffer, bufsize, NULL);
	cout << buffer << endl;

	system("pause");

	closesocket(connection);
	WSACleanup();
	return 0;
}