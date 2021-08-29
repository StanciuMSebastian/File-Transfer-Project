#include "winsockConnect.h"

bool winsockConnect::Connect()
{
    bool connected = false;

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {
        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return false;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            std::cout << "Could not connect to server, error: " << WSAGetLastError() << std::endl;
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        else
        {
            connected = true;
            break;
        }
    }

    return connected;
}

bool winsockConnect::sendBool(bool val)
{
    int returncheck = send(ConnectSocket, (char*)&val, sizeof(bool), NULL);
    if (returncheck == SOCKET_ERROR)
        return false;

    return true;
}

bool winsockConnect::getBool(bool& val)
{
    int returncheck = recv(ConnectSocket, (char*)&val, sizeof(bool), NULL);
    if (returncheck == SOCKET_ERROR)
        return false;

    return true;
}


bool winsockConnect::sendInt(const int& val)
{
    int returncheck = send(ConnectSocket, (char*)&val, sizeof(int), NULL);
    if (returncheck == SOCKET_ERROR)
        return false;

    return true;
}

bool winsockConnect::getInt(int& val)
{
    int returncheck = recv(ConnectSocket, (char*)&val, sizeof(int), NULL);
    if (returncheck == SOCKET_ERROR)
        return false;

    return true;
}

bool winsockConnect::sendCharString(char* chr, int size)
{
    int returncheck = send(ConnectSocket, chr, size, NULL);
    if (returncheck == SOCKET_ERROR)
        return false;

    return true;
}

bool winsockConnect::getCharString(char* &chr, int size)
{
    int returncheck = recv(ConnectSocket, chr, size, NULL);
    if (returncheck == SOCKET_ERROR)
        return false;

    return true;
}

bool winsockConnect::sendPacketType(const PACKET& packetType)
{
    int returnCheck = send(ConnectSocket, (char*)&packetType, sizeof(PACKET), NULL);
    if (returnCheck == SOCKET_ERROR)
        return false;
    
    std::cout << "Sent packet Type " << packetType << std::endl;
    return true;
}

bool winsockConnect::getPacketType(PACKET& packetType)
{
    int returnCheck = recv(ConnectSocket, (char*)&packetType, sizeof(PACKET), NULL);
    if (returnCheck == SOCKET_ERROR)
        return false;

    std::cout << "Received Packet Type: " << packetType << std::endl;
    return true;
}


bool winsockConnect::sendString(const std::string& val)
{
    int bufferlen = val.size();
    if (!sendInt(bufferlen))
        return false;

    int returncheck = send(ConnectSocket, val.c_str(), bufferlen, NULL);
    if (returncheck == SOCKET_ERROR)
        return false;

    return true;
}

bool winsockConnect::getString(std::string& val)
{
    int bufferlen = 0;
    if (!getInt(bufferlen))
        return false;

    char* buffer = new char[bufferlen + 1];
    buffer[bufferlen] = '\0';

    int returncheck = recv(ConnectSocket, buffer, bufferlen, NULL);
    val = buffer;
    delete[] buffer;

    if (returncheck == SOCKET_ERROR)
        return false;

    return true;
}


//bool winsockConnect::getVector(int id,std::vector<std::string>& v)
//{
//    int bufferlen = 0;
//    if (!getInt(bufferlen))
//        return false;
//
//    /*char* buffer = new char[bufferlen + 1];
//    buffer[bufferlen] = '\0';*/
//    std::vector<std::string> buffer;
//
//
//    int returncheck = recv(ConnectSocket, (char*)buffer.data(), bufferlen, NULL);
//    for (int i = 0; i < buffer.size(); i++)
//    {
//        v.push_back(buffer[i]);
//    }
//    buffer.clear();
//
//    if (returncheck == SOCKET_ERROR)
//        return false;
//
//    return true;
//}

bool winsockConnect::closeConnection()
{
    if (closesocket(ConnectSocket == SOCKET_ERROR))
    {
        if (WSAGetLastError() == WSAENOTSOCK)
            return true;

        std::cout << "Failed to close the socket. Winsock error: " << std::to_string(WSAGetLastError()) << std::endl;
        return false;
    }

    return true;
}