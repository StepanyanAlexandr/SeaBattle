#include "Connection.h"

SOCKET Connection::listener = NULL;

Connection::Connection()
{
	libversion = MAKEWORD(2, 2);
	inaddrsize = sizeof(inaddr);
}

bool Connection::Init()
{
	if (WSAStartup(libversion, &wsadata))
	{
		cerr << "Error: Could not initialize winsock." << endl;
		return false;
	}
	
	inaddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.106");
	inaddr.sin_port = htons(1701);
	inaddr.sin_family = AF_INET;

	if (listener == NULL)
	{
		if ((listener = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
		{
			cerr << "Error: " << WSAGetLastError() << " - Could not create a listener socket." << endl;
			return false;
		}
		if (bind(listener, (SOCKADDR*)&inaddr, inaddrsize) == SOCKET_ERROR)
		{
			cout << "Error: " << WSAGetLastError() << " - Could not bind listener" << endl;
			return false;
		}
		if (listen(listener, 1) == SOCKET_ERROR)
		{
			cout << "Error: " << WSAGetLastError() << " - Could not start listening" << endl;
			return false;
		}
	}

	return true;
}

bool Connection::Connect()
{
	if ((connection = accept(listener, (SOCKADDR*)&inaddr, &inaddrsize)) == 0)
	{
		cout << "Error: " << WSAGetLastError() << " - Could not connected to server" << endl;
		return false;
	}

	return true;
}

void Connection::Close()
{
	closesocket(listener);
	closesocket(connection);
	WSACleanup();
}