#pragma once

#include "winsockConnect.h"
#include "qstring.h"
#include <QFile>
#include <fstream>
#include <thread>

class UploadDialog;

class Client:
	public winsockConnect
{
private:
	
	std::string rank;
	int ID;
	std::thread clientThread;

	 std::string username;
	std::string password;

	static Client* instance;

	bool checkUsername(std::string);
	bool checkPassword(std::string);

	int countBars(std::string);

	static void clientHandler();
	Client();
public:
	std::string getRank() { return this->rank; }
	std::string getUsername() { return this->username; }
	int getID() { return this->ID; };

	bool processPacket(PACKET packetType);
	bool login(std::string username, std::string password);
	bool sendFile(QString& Qfilepath, QString& Qfilename, UploadDialog* dialog);
	bool signup(std::string, std::string);
	std::string getFile(QString& filename);
	inline void StartSubRoutine() { clientThread = std::thread(clientHandler); }

	Client* getInstance();

	~Client();
};

