#include "Connection.h"

Connection::Connection()
{
	wsadata = new WSADATA;
	memset(&wsadata, NULL, sizeof(wsadata));

	libversion = MAKEWORD(2, 2);

	serveraddr = new SOCKADDR_IN;
	memset(&serveraddr, NULL, sizeof(serveraddr));

	memset(&server, NULL, sizeof(server));
	serveraddrsize = sizeof(serveraddr);
}

Connection::~Connection()
{
	delete wsadata;
	delete serveraddr;
}

int Connection::Init()
{
	if (WSAStartup(libversion, wsadata))
	{
		cerr << "Error: Could not initialize winsock." << endl;
		return WSASTARTUPFAILURE;
	}

	if ((server = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
	{
		cerr << "Error: " << WSAGetLastError() << " - Could not create a socket." << endl;
		return INVALID_SOCKET;
	}

	serveraddr->sin_addr.S_un.S_addr = inet_addr("192.168.0.106");
	serveraddr->sin_port = htons(1600);
	serveraddr->sin_family = AF_INET;

	if (connect(server, (SOCKADDR*)serveraddr, serveraddrsize) == SOCKET_ERROR)
	{
		cout << "Error: " << WSAGetLastError() << "Could not connected to server" << endl;
		return SOCKET_ERROR;
	}

	return 1;
}

void Connection::Close()
{
	closesocket(server);
	WSACleanup();
}