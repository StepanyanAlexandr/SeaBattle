#include "Connection.h"

SOCKET Connection::listener = NULL;
ofstream logfile;

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
	if ((connection = accept(listener, (SOCKADDR*)&inaddr, &inaddrsize)) == INVALID_SOCKET)
		throw "Failed to connect user.";
	else
	{
		isconnect = true;

		unsigned long param = 1;
		if (ioctlsocket(connection, FIONBIO, &param) == SOCKET_ERROR)
			throw "Can't create non-bloking socket";
	}
}

void Connection::Close()
{
	if (listener != NULL) { closesocket(listener); listener = NULL; }
	if (connection != NULL) { closesocket(connection); connection = NULL; }
	WSACleanup();
	isconnect = false;
}

void Connection::MessageSend(string &message)
{
	send(connection, message.c_str(), BUFFERSIZE, 0);
	logfile << "    <-   " << message << endl;
}

int Connection::MessageReceve()
{ 
	char buffer[BUFFERSIZE];
	int ret = recv(connection, buffer, BUFFERSIZE, 0);
	if (ret != NOMESSAGE)
	{
		lastinmsg = buffer;
		logfile << "    ->   " << lastinmsg << endl;
	}
	return ret;
}