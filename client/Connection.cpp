#include "Connection.h"

Connection::Connection()
{
	libversion = MAKEWORD(2, 2);
	serveraddrsize = sizeof(serveraddr);
	server = NULL;
}

bool Connection::Init(const char *address)
{
	if (WSAStartup(libversion, &wsadata))
	{
		cerr << "Error: Could not initialize winsock." << endl;
		return false;
	}

	if ((server = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
	{
		cerr << "Error: " << WSAGetLastError() << " - Could not create a socket." << endl;
		return false;
	}

	serveraddr.sin_addr.S_un.S_addr = inet_addr(address);
	serveraddr.sin_port = htons(1701);
	serveraddr.sin_family = AF_INET;

	return true;
}

bool Connection::Connect()
{
	if (connect(server, (SOCKADDR*)&serveraddr, serveraddrsize) == SOCKET_ERROR)
	{
		cout << "Error: " << WSAGetLastError() << " - Could not connected to server" << endl;
		return false;
	}

	return true;
}

void Connection::Close()
{
	closesocket(server);
	WSACleanup();
}