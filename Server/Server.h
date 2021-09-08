#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "packet.h"
#include"IUser.h"
#include"AllUsers.h"
#include"AllFiles.h"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#define DEFAULT_PORT "25565"


class BazaDeDate;

class Server
{
private:
	static Server* instance;

	SOCKET Connections[100];
	std::thread connectionThreads[100];

	addrinfo* result;
	addrinfo hints;
	SOCKET ListenSocket;
	int iResult;

	int ConnectionCounter = 0;
	

	//void Getusername(int id);

	bool GetInt(int id, int& value);
	bool SendInt(int id, int& value);

	bool GetBool(int id, bool& value);
	bool SendBool(int id, bool value);

	bool GetString(int id, std::string& value);
	bool SendString(int id, const std::string& value);

	bool sendVector(int id, const std::vector<string>& v);

	bool SendPacketType(int id, const PACKET& packetType);
	bool GetPacketType(int id, PACKET& packetType);
	bool ProcessPacket(int index, PACKET packetType);

	bool CloseConnection(int index);

	void loadUsers();
	static void ClientHandler(int index);
	BazaDeDate* bd;
    
public:
	Server();
	static Server* getInstance();
	bool ListenForNewConnection();

	~Server();

protected:
	int lastID = 0;
	static int fileID;
	std::vector<IUser*> users = {};
};

