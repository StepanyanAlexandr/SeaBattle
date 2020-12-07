#pragma once
#include "Connection.h"

int main(int argc, char *argv[])
{
	Connection connections[2];

	if (!connections[0].Init())
	{
		cout << "first connection initialize failure" << endl;
		system("pause");
		return -1;
	}
	if (!connections[1].Init())
	{
		cout << "second connection initialize failure" << endl;
		system("pause");
		return -2;
	}

	char buffer[BUFFERSIZE];

	if (!connections[0].Connect())
	{
		system("pause");
		return -1;
	}

	cout << "First connection succesfull" << endl;
	connections[0].MessageReceve(buffer);
	cout << buffer << endl;
	memcpy(buffer, "Hello client1\n\0", BUFFERSIZE);
	connections[0].MessageSend(buffer);

	if (!connections[1].Connect())
	{
		system("pause");
		return -2;
	}

	cout << "Second connection succesfull" << endl;
	connections[1].MessageReceve(buffer);
	cout << buffer << endl;
	memcpy(buffer, "Hello client2\n\0", BUFFERSIZE);
	connections[1].MessageSend(buffer);
	



	
	
	
	
	
	connections[0].Close();
	connections[0].Close();

	system("pause");
	return 0;
}