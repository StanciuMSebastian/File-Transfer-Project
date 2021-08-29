#include "Client.h"
#include"AllUsers.h"
#include"AllFiles.h"
#include "UploadDialog.h"

Client* Client::instance = 0;

Client* Client::getInstance()
{
	if (!instance)
	{
		instance = new Client();
	}

	return instance;
}

bool Client::checkUsername(std::string username)
{
	if (username.size() < 5)//username-ul trebuie sa aibe mai mult de 6 caractere
		return false;

	if (strchr(username.c_str(), ' ') || strchr(username.c_str(), '!') || strchr(username.c_str(), '\t')
		|| strchr(username.c_str(), '@') || strchr(username.c_str(), '#') || strchr(username.c_str(), '$')
			|| strchr(username.c_str(), '%') || strchr(username.c_str(), '^') || strchr(username.c_str(), '&')
				|| strchr(username.c_str(), '*') || strchr(username.c_str(), '(') || strchr(username.c_str(), ')'))
					return false;

	return true;
}

bool Client::checkPassword(std::string password)
{
	if (password.size() < 7)//parola trebuie sa aibe minim 8 caractere
		return false;

	if (strchr(password.c_str(), ' ') || strchr(password.c_str(), '\t'))
		return false;

	return true;
}

int Client::countBars(std::string str)
{
	int count = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '/')
			count++;
	}

	return count;
}

void Client::clientHandler()
{
	PACKET packetType;
	while (true)
	{
		if (!instance->getPacketType(packetType))
			break;

		if (!instance->processPacket(packetType))
			break;
	}

	std::cout << "Connection lost" << std::endl;

	if (instance->closeConnection())
	{
		std::cout << "Socket to server was closed succesfully" << std::endl;
	}
}

Client::Client()
{
	this->Connect();
	this->rank = "User";
	//this->StartSubRoutine();
}

bool Client::processPacket(PACKET packetType)
{
	switch (packetType)
	{
	case P_Login:
	{
		if (!getString(this->rank))
			return false;
		if (!getInt(this->ID))
			return false;

		break;
	}
	case P_Signup:
	{
		if (!getInt(this->ID))
			return false;
		break;
	}
	case P_Download:
	{
		//todo
		break;
	}
	case P_Upload:
	{
		//todo

		break;
	}
	default:
		std::cout << "Unrecognized packet: " << packetType << std::endl;
	}

	return true;
}

bool Client::login(std::string username, std::string password)
{
	bool userAccepted = false;
	this->sendPacketType(P_Login);

	this->sendString(username);
	this->getBool(userAccepted);
	if (userAccepted == false)
		return false;

	this->sendString(password);
	this->getBool(userAccepted);
	if (userAccepted == false)
		return false;
	//baga toate fisierele uploadate
	std::string filename ="";
	this->getString(filename);
	while (filename!="end")
	{
		this->getString(filename);
		AllFiles::Files.push_back(filename);
	}
	this->processPacket(P_Login);
	this->getBool(userAccepted);
	if (userAccepted == false)
		return false;

	this->username = username;
	this->password = password;
	
	return true;
}
std::string Client::getFile(QString& filepath)
{
	std::string buffer = filepath.toUtf8().constData();
	int k = countBars(buffer);
	std::string filename = strtok((char*)buffer.c_str(), "/");


	for (int i = 0; i < k; i++)
	{
		filename = strtok(NULL, "/\0");
	}
	return filename;
}
bool Client::sendFile(QString& Qfilepath, QString& Qfilename, UploadDialog* dialog)
{
	std::string buffer;
	std::string filename = Qfilename.toUtf8().constData();
	std::string filepath = Qfilepath.toUtf8().constData();

	if (!this->sendPacketType(P_Upload))
		return false;

	if (!this->sendString(this->username))
		return false;
	if (!this->sendString(filename))
		return false;

	this->getString(buffer);

	std::string usernames = "";
	while (buffer != "end")
	{
		usernames += buffer + ",";
		this->getString(buffer);
	}

	buffer = dialog->open(usernames);
	delete dialog;

	this->sendString(buffer);


	std::ifstream file;
	file.open(filepath, std::ios::binary);

	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	
	char* fileContents = new char[fileSize];
	file.read(fileContents, fileSize);
	fileContents[fileSize] = '\0';

	this->sendInt(fileSize);

	this->sendCharString(fileContents, fileSize);

	file.close();

	AllFiles::Files.push_back(filename);

	//this->sendString(fileContainer);
	//std::cout << fileContainer << std::endl;

	return true;
}

bool Client::signup(std::string username, std::string password)
{
	if (!this->checkPassword(password))
		return false;

	if (!this->checkUsername(username))
		return false;

	bool userAccepted = false;
	this->sendPacketType(P_Signup);

	this->sendString(username);
	this->getBool(userAccepted);

	this->sendString(password);
	this->getBool(userAccepted);

	this->processPacket(P_Signup);
	this->getBool(userAccepted);

	this->username = username;
	this->password = password;

	return userAccepted;
}

Client::~Client()
{
	this->instance = 0;
	this->username = "";
	this->password = "";
}