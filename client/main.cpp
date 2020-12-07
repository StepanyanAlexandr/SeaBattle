#pragma once
#include "App.h"

int main(int argc, char *argv[])
{
	Connection connection;

	if (!connection.Init())
	{
		system("Pause");
		return -1;
	}
	if (!connection.Connect())
	{
		system("pause");
		return -1;
	}

	char buffer[BUFFERSIZE] = "1";
	connection.MessageSend(buffer);
	connection.MessageReceve(buffer);
	cout << buffer << endl;
	


	
	
	
	
	
	connection.Close();
	system("pause");
	return 0;
}