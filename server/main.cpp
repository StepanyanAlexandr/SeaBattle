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
	inaddr.sin_addr.S_un.S_addr = htons(INADDR_ANY);
	inaddr.sin_port = htons(1600);
	inaddr.sin_family = AF_INET;

	SOCKET listener = socket(AF_INET, SOCK_STREAM, NULL);
	if (listener == SOCKET_ERROR)
	{
		cout << "Error: socket was not created" << endl;
		return 2;
	}
	if (bind(listener, (SOCKADDR*)&inaddr, inaddrsize) == SOCKET_ERROR)
	{
		cout << "Error: binding failure" << endl;
		return 3;
	}
	if (listen(listener, SOMAXCONN) == SOCKET_ERROR)
	{
		cout << "Error: socket did not start listening" << endl;
		return 4;
	}

	SOCKET connections[2];
	if ((connections[0] = accept(listener, (SOCKADDR*)&inaddr, &inaddrsize)) == 0)
	{
		cout << "Error: first client was not connected" << endl;
	}
	cout << "First connection succesfull" << endl;
	
	if ((connections[1] = accept(listener, (SOCKADDR*)&inaddr, &inaddrsize)) == 0)
	{
		cout << "Error: second client was not connected" << endl;
	}
	cout << "Second connection succesfull" << endl;

	int bufsize = 256;
	char buffer[256] = "Hello client\n";
	send(connections[0], buffer, bufsize, NULL);
	send(connections[1], buffer, bufsize, NULL);

	system("pause");

	closesocket(listener);
	closesocket(connections[0]);
	closesocket(connections[1]);
	WSACleanup();
	return 0;
}