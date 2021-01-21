#include "Connection.h"

SOCKET Connection::listener = NULL;

Connection::Connection()
{
	libversion = MAKEWORD(2, 2);
	inaddrsize = sizeof(inaddr);
	connection = NULL;
	isconnect = false;
}

void Connection::Init()
{
	if (WSAStartup(libversion, &wsadata))
		throw "Could not initialize winsock.";
	
	inaddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.106");
	inaddr.sin_port = htons(1701);
	inaddr.sin_family = AF_INET;

	if (listener == NULL)
	{
		if ((listener = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw "Could not create a listener socket.";
		if (bind(listener, (SOCKADDR*)&inaddr, inaddrsize) == SOCKET_ERROR)
			throw "Could not bind listener.";
		if (listen(listener, 1) == SOCKET_ERROR)
			throw "Could not start listening.";
	}
}

void Connection::Connect()
{
	if ((connection = accept(listener, (SOCKADDR*)&inaddr, &inaddrsize)) == 0)
		isconnect = false;
	else
		isconnect = true;
}

void Connection::Close()
{
	if (listener != NULL) closesocket(listener);
	if (connection != NULL) closesocket(connection);
	WSACleanup();
}