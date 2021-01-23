#pragma once
#include "Field.h"

int main(int argc, char *argv[])
{
	string message[2];
	Connection connections[2];
	Field **fields = nullptr;

	logfile.open("logfile.txt", ios_base::out);
	int turn = FIRSTPLAYER;
	int win = -1;

	while (true)
	{
		turn = FIRSTPLAYER;
		win = -1;
		fields = new Field*[2];

		try
		{
			connections[FIRSTPLAYER].Init();
			connections[SECONDPLAYER].Init();
		}
		catch (const char *errormessage)
		{
			logfile << errormessage << endl;
			logfile << "Initialization failed" << endl;
			logfile.close();
			return -1;
		}
		logfile << "Initialization successful" << endl;

		try { connections[FIRSTPLAYER].Connect(); }
		catch (const char *errormessage)
		{
			logfile << errormessage << endl;
			logfile.close();
			return -1;
		}
		logfile << "First connection succesful" << endl;
		// принимаем сообщение со занчениями клеток поля первого игрока
		connections[FIRSTPLAYER].MessageReceve();
		message[FIRSTPLAYER] = connections[FIRSTPLAYER].getLastInputMessage();
		fields[FIRSTPLAYER] = new Field(message[FIRSTPLAYER]);
		message[FIRSTPLAYER] = "yourturn:";
		connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);

		try { connections[SECONDPLAYER].Connect(); }
		catch (const char *errormessage)
		{
			logfile << errormessage << endl;
			logfile.close();
			return -1;
		}
		logfile << "Second connection succesful" << endl;
		// принимаем сообщение со занчениями клеток поля второго игрока
		connections[SECONDPLAYER].MessageReceve();
		message[SECONDPLAYER] = connections[SECONDPLAYER].getLastInputMessage();
		fields[SECONDPLAYER] = new Field(message[SECONDPLAYER]);
		message[SECONDPLAYER] = "enemyturn:";
		connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);

		bool running = true;
		while (running)
		{
			connections[FIRSTPLAYER].MessageReceve();
			connections[SECONDPLAYER].MessageReceve();
			message[FIRSTPLAYER] = connections[FIRSTPLAYER].getLastInputMessage();
			message[SECONDPLAYER] = connections[SECONDPLAYER].getLastInputMessage();

			if (turn == FIRSTPLAYER)
			{
				logfile << "FIRSTPLAYER turn:" << endl;

				if (message[FIRSTPLAYER] == "disconnect:")
				{
					if (message[SECONDPLAYER] == "ping:")
					{
						message[SECONDPLAYER] = "win:";
						connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);
					}
					running = false;
				}
				else if (message[FIRSTPLAYER].find("hit:") != string::npos)
				{
					string msg = message[SECONDPLAYER];

					int x = (message[FIRSTPLAYER][4] - '0'), y = (message[FIRSTPLAYER][6] - '0');
					CELLTYPE type = fields[SECONDPLAYER]->hitType(x, y);

					if (type == MISS)
					{
						message[FIRSTPLAYER] = "enemy:M:";

						message[SECONDPLAYER] = "player:M:";
						message[SECONDPLAYER] += (x + '0');
						message[SECONDPLAYER] += ':';
						message[SECONDPLAYER] += (y + '0');
						message[SECONDPLAYER] += ':';

						fields[SECONDPLAYER]->setMiss(x, y);
					}
					else if (type == HIT)
					{
						message[FIRSTPLAYER] = "enemy:H:";

						message[SECONDPLAYER] = "player:H:";
						message[SECONDPLAYER] += (x + '0');
						message[SECONDPLAYER] += ':';
						message[SECONDPLAYER] += (y + '0');
						message[SECONDPLAYER] += ':';

						fields[SECONDPLAYER]->setHit(x, y);
					}
					else if (type == DESTROY)
					{
						message[FIRSTPLAYER] = "enemy:D:";

						message[SECONDPLAYER] = "player:D:";
						message[SECONDPLAYER] += (x + '0');
						message[SECONDPLAYER] += ':';
						message[SECONDPLAYER] += (y + '0');
						message[SECONDPLAYER] += ':';

						fields[SECONDPLAYER]->destroyShip(x, y);
					}

					if (msg == "disconnect:")
					{
						connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);
						message[FIRSTPLAYER] = "win:";
						connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);

						running = false;
					}
					else if (msg == "ping:")
					{
						connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);
						connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);

						if (fields[SECONDPLAYER]->isWin())
						{
							message[FIRSTPLAYER] = "win:";
							message[SECONDPLAYER] = "lose:";

							connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);
							connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);

							running = false;
						}
						else
						{
							message[FIRSTPLAYER] = "ping:";
							message[SECONDPLAYER] = "ping:";

							connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);
							connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);

							turn = SECONDPLAYER;
						}
					}
				}
				else if (message[FIRSTPLAYER] == "ping:")
				{
					if (message[SECONDPLAYER] == "disconnect:")
					{
						message[FIRSTPLAYER] = "win:";
						connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);

						running = false;
					}
					else if (message[SECONDPLAYER] == "ping:")
					{
						message[FIRSTPLAYER] = "ping:";
						message[SECONDPLAYER] = "ping:";

						connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);
						connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);
					}
				}
			}
			else
			{
				logfile << "SECONDPLAYER turn:" << endl;

				if (message[SECONDPLAYER] == "disconnect:")
				{
					if (message[FIRSTPLAYER] == "ping:")
					{
						message[FIRSTPLAYER] = "win:";
						connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);
					}
					running = false;
				}
				else if (message[SECONDPLAYER].find("hit:") != string::npos)
				{
					string msg = message[FIRSTPLAYER];

					int x = (message[SECONDPLAYER][4] - '0'), y = (message[SECONDPLAYER][6] - '0');
					CELLTYPE type = fields[FIRSTPLAYER]->hitType(x, y);

					if (type == MISS)
					{
						message[SECONDPLAYER] = "enemy:M:";

						message[FIRSTPLAYER] = "player:M:";
						message[FIRSTPLAYER] += (x + '0');
						message[FIRSTPLAYER] += ':';
						message[FIRSTPLAYER] += (y + '0');
						message[FIRSTPLAYER] += ':';

						fields[FIRSTPLAYER]->setMiss(x, y);
					}
					else if (type == HIT)
					{
						message[SECONDPLAYER] = "enemy:H:";

						message[FIRSTPLAYER] = "player:H:";
						message[FIRSTPLAYER] += (x + '0');
						message[FIRSTPLAYER] += ':';
						message[FIRSTPLAYER] += (y + '0');
						message[FIRSTPLAYER] += ':';

						fields[FIRSTPLAYER]->setHit(x, y);
					}
					else if (type == DESTROY)
					{
						message[SECONDPLAYER] = "enemy:D:";

						message[FIRSTPLAYER] = "player:D:";
						message[FIRSTPLAYER] += (x + '0');
						message[FIRSTPLAYER] += ':';
						message[FIRSTPLAYER] += (y + '0');
						message[FIRSTPLAYER] += ':';

						fields[FIRSTPLAYER]->destroyShip(x, y);
					}

					if (msg == "disconnect:")
					{
						connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);
						message[SECONDPLAYER] = "win:";
						connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);

						running = false;
					}
					else if (msg == "ping:")
					{
						connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);
						connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);

						if (fields[FIRSTPLAYER]->isWin())
						{
							message[SECONDPLAYER] = "win:";
							message[FIRSTPLAYER] = "lose:";

							connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);
							connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);

							running = false;
						}
						else
						{
							message[SECONDPLAYER] = "ping:";
							message[FIRSTPLAYER] = "ping:";

							connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);
							connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);

							turn = FIRSTPLAYER;
						}
					}
				}
				else if (message[SECONDPLAYER] == "ping:")
				{
					if (message[FIRSTPLAYER] == "disconnect:")
					{
						message[SECONDPLAYER] = "win:";
						connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);

						running = false;
					}
					else if (message[FIRSTPLAYER] == "ping:")
					{
						message[FIRSTPLAYER] = "ping:";
						message[SECONDPLAYER] = "ping:";

						connections[SECONDPLAYER].MessageSend(message[SECONDPLAYER]);
						connections[FIRSTPLAYER].MessageSend(message[FIRSTPLAYER]);
					}
				}
			}
			logfile << endl;
		}

		connections[0].Close();
		connections[1].Close();

		delete fields[FIRSTPLAYER];
		delete fields[SECONDPLAYER];
		delete[] fields;
	}

	logfile << "The server has been shut down" << endl;
	logfile.close();

	return 0;
}