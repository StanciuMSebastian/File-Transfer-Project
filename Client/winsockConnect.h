#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>
#include<vector>
#include <string>
#include "packet.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_IP "192.168.1.69"//trebuie introdus ip-ul corect- ip local: 192.168.1.69
#define DEFAULT_PORT "25565"//default 25565


class winsockConnect
{
private:

    SOCKET ConnectSocket = INVALID_SOCKET;

    addrinfo* result = NULL;
    addrinfo* ptr = NULL;
    addrinfo hints;
    int iResult;

protected:


    bool getBool(bool& val);
    bool sendBool(bool val);

   
    bool processPacket(PACKET packetType);

    bool closeConnection();
public:
    bool sendInt(const int& val);
    bool getInt(int& val);

    bool sendCharString(char*chr, int size);
    bool getCharString(char* &chr, int size);

    bool sendPacketType(const PACKET& packetType);
    bool getPacketType(PACKET& packetType);
    bool sendString(const std::string& val);
    bool getString(std::string& val);

    //bool getVector(int id, std::vector<std::string>& v);

    void winsockInnit();
    bool Connect();


    winsockConnect() 
    {
        WSADATA wsaData;

        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
            return;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
        iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);
        if (iResult != 0) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
            return;
        }
    }
};

