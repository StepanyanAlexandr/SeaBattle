#include "Connection.h"

Connection::Connection()
{
	libversion = MAKEWORD(2, 2);
	serveraddrsize = sizeof(serveraddr);
	server = NULL;
	isconnect = false;
}

void Connection::Init()
{
	if (WSAStartup(libversion, &wsadata))
		throw "Couldn't initialize winsock";
	if ((server = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
		throw "Couldn't create a socket";

	serveraddr.sin_addr.S_un.S_addr = inet_addr(SERVERADDRESS);
	serveraddr.sin_port = htons(1701);
	serveraddr.sin_family = AF_INET;
}

void Connection::Connect()
{
	if (connect(server, (SOCKADDR*)&serveraddr, serveraddrsize) == SOCKET_ERROR)
		isconnect = false;
	else
		isconnect = true;
}

void Connection::Close()
{
	closesocket(server);
	WSACleanup();
}

void Connection::MessageReceve()
{
	char buffer[BUFFERSIZE];
	recv(server, buffer, BUFFERSIZE, 0);
	lastinmsg = buffer;
}