#pragma once
#include "Connection.h"

int main(int argc, char *argv[])
{
	Connection connections[2];

	try
	{
		connections[0].Init();
		connections[1].Init();
	}
	catch (const char *errormessage)
	{
		cout << errormessage << endl;
		system("pause");
		return -1;
	}

	try { connections[0].Connect(); }
	catch(const char *errormessage)
	{
		cout << errormessage << endl;
		system("pause");
		return -1;
	}
	cout << "First connection succesfull" << endl;
	//connections[0].MessageReceve(buffer);
	//cout << buffer << endl;
	//memcpy(buffer, "Hello client1\n\0", BUFFERSIZE);
	//connections[0].MessageSend(buffer);

	try { connections[1].Connect(); }
	catch (const char *errormessage)
	{
		cout << errormessage << endl;
		system("pause");
		return -1;
	}
	cout << "Second connection succesfull" << endl;	
	//connections[1].MessageReceve(buffer);
	//cout << buffer << endl;
	//memcpy(buffer, "Hello client2\n\0", BUFFERSIZE);
	//connections[1].MessageSend(buffer);
	



	
	
	
	
	
	connections[0].Close();
	connections[1].Close();

	system("pause");
	return 0;
}