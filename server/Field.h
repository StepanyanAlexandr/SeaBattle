#pragma once

#include <string>
using namespace std;

class Protocol
{
private:
	string *commands;
public:
	Protocol() { commands = nullptr; }
	~Protocol() { if (commands != nullptr) delete[] commands; }

	void LoadProtocol();
};

void Protocol::LoadProtocol()
{

}