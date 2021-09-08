#include "Server.h"
#include"User.h"
#include"File.h"
#include"BazaDeDate.h"
Server* Server::instance = nullptr;
int Server::fileID=0;
Server* Server::getInstance()
{
	if (!instance)
	{
		instance = new Server();
	}

	return instance;
}

Server::Server()
{
    loadUsers();
    WSADATA wsaData;
    
    ListenSocket = INVALID_SOCKET;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    //de incarcat toti userii mereu intr-un vector/clasa
}

bool Server::GetInt(int id, int& value)
{
    int returnCheck = recv(Connections[id], (char*)&value, sizeof(int), NULL);
    if (returnCheck == SOCKET_ERROR)
        return false;
    return true;
}

bool Server::SendInt(int id, int& value)
{
    int returnCheck = send(Connections[id], (char*)&value, sizeof(int), NULL);
    if (returnCheck == SOCKET_ERROR)
        return false;
    return true;
}

bool Server::GetBool(int id, bool& value)
{

    int returnCheck = recv(Connections[id], (char*)&value, sizeof(bool), NULL);
    if (returnCheck == SOCKET_ERROR)
        return false;
    return true;
}

bool Server::SendBool(int id, bool value)
{
    int returnCheck = send(Connections[id], (char*)&value, sizeof(bool), NULL);
    if (returnCheck == SOCKET_ERROR)
        return false;
    return true;
}


bool Server::GetString(int id, std::string& value)
{
    int buffLength = 0;
    if (!GetInt(id, buffLength))
        return false;

    char* buffer = new char[buffLength + 1];

    int returnCheck = recv(Connections[id], buffer, buffLength, NULL);
    buffer[buffLength] = '\0';
    value = buffer;
    delete[] buffer;

    if (returnCheck == SOCKET_ERROR)
        return false;
    
    return true;
}

bool Server::SendString(int id, const std::string& value)
{
    int bufferLength = value.size();
    if (!SendInt(id, bufferLength))
        return false;

    int returnCheck = send(Connections[id], value.c_str(), bufferLength, NULL);
    if (returnCheck == SOCKET_ERROR)
        return false;
    return true;
}


bool verifyUsername(std::string username1, std::string username2)
{
    for (int i = 0; i < username1.size(); i++)
        username1[i] = tolower(username1[i]);
    for (int i = 0; i < username2.size(); i++)
        username2[i] = tolower(username2[i]);

    if (username1 == username2)
        return false;

    return true;
}


bool Server::GetPacketType(int id, PACKET& packetType)
{
    int returnCheck = recv(Connections[id], (char*)&packetType, sizeof(PACKET), NULL);
    if (returnCheck == SOCKET_ERROR)
        return false;

    std::cout << "Received Packet Type: " << packetType << std::endl;
    return true;
}


bool Server::SendPacketType(int id, const PACKET& packetType)
{
    int returnCheck = send(Connections[id], (char*)&packetType, sizeof(PACKET), NULL);
    if (returnCheck == SOCKET_ERROR)
        return false;

    std::cout << "Sent packet Type " << packetType << std::endl;
    return true;
}


bool hasPrivilage(std::string username, std::string allUsernames)
{
    std::string individualUsername = "";

    allUsernames+= ",";

    for (int i = 0; i < allUsernames.size(); i++)
    {
        if (individualUsername == "done")
            return false;

        if (allUsernames[i] == ',')
        {
            if (individualUsername == username)
                return true;
            else
                individualUsername = "";
        }
        else
            individualUsername += allUsernames[i];
    }

    return false;
}

bool Server::ProcessPacket(int index, PACKET packetType)
{
    switch (packetType)
    {
    case P_Chg_password:
    {
        string new_Password;
        int ID;
        this->GetInt(index, ID);
        this->GetString(index, new_Password);
        bd->executeQuery(UPDATE, ID, new_Password);

        AllUsers::ListOfUsers[ID]->setPassword(new_Password);

        break;
    }
    case P_Upload:
    {        //create a new insert in a table
        std::string filename;
        std::string buffer;
        std::string uploaderUsername;
        int ID = -1;

        this->GetString(index, uploaderUsername);
        for (int i = 0; i < AllUsers::ListOfUsers.size(); i++)
        {
            if (AllUsers::ListOfUsers[i]->getUsername() == uploaderUsername)
            {
                ID = AllUsers::ListOfUsers[i]->getID();
                break;
            }
        }

        if (ID == -1)
        {
            std::cout << "User necunoscut cu username-ul : " << uploaderUsername << " a incercat sa uploadeze."
                << std::endl;

            return false;
        }

        this->GetString(index, filename);
        //this->GetString(index, buffer);
        for (int i = 0; i < AllUsers::ListOfUsers.size(); i++)
        {
            if (AllUsers::ListOfUsers[i]->getUsername() != AllUsers::ListOfUsers[ID]->getUsername())
                this->SendString(index, AllUsers::ListOfUsers[i]->getUsername());
        }
        this->SendString(index, "end");
        this->GetString(index, buffer);

        string usernames = buffer.substr(0, buffer.size() - 5);


        bd->executeQuery(INSERT, new File(filename, AllUsers::ListOfUsers[ID]->getUsername(), usernames));
        AllFiles::ListofFiles.push_back(new File(filename, AllUsers::ListOfUsers[ID]->getUsername(), usernames));
        fileID++;


        int fileSize;
        this->GetInt(index, fileSize);
        char* filecontents = new char[fileSize];

        ofstream file("E:\\Files\\" + filename, std::ios::binary);
        
        recv(Connections[index], filecontents, fileSize, NULL);
        filecontents[fileSize] = '\0';

        file.write(filecontents, fileSize);

        file.close();

        break;
    }
    case P_Download:
    {
        std::string filename = "";
        std::string filepath = "E:\\Files\\";
        std::string username;
        int ID;

        this->GetInt(index, ID);
        this->GetString(index, filename);

        //username = AllUsers::ListOfUsers[ID]->getUsername();
        ifstream fileItself(filepath + filename, std::ios::binary);
        int fileSize;
        fileItself.seekg(0, std::ios::end);
        fileSize = fileItself.tellg();
        fileItself.seekg(0, std::ios::beg);

        char* fileContents = new char[fileSize];
        fileItself.read(fileContents, fileSize);
        fileContents[fileSize] = '\0';

        this->SendInt(index, fileSize);

        send(Connections[index], fileContents, fileSize, NULL);

        fileItself.close();

        //while(filename != "done")
        //{
        //    for (int i = 0; i < AllFiles::ListofFiles.size(); i++)
        //    {
        //       // if ((hasPrivilage(username, AllFiles::ListofFiles[i]->getUsernames()) || username == AllFiles::ListofFiles[i]->getUploader()) && filename == AllFiles::ListofFiles[i]->getDenumire())
        //        //{

        //            
        //        //}
        //    }

        //    if(filename == "")
        //    {
        //        this->SendString(index, "");
        //        std::cout << "Userul " << username << " nu are permisiunea la fisierul " << filename << std::endl;
        //    }
        //    this->GetString(index, filename);
        //}


        break;
    }
    case P_Login:
    {
        std::string username;
        std::string password;
        int ID = 0;

        this->GetString(index, username);
        bool okay = false;
        for (int i=0;i<AllUsers::ListOfUsers.size();i++)
        {
            if (username == AllUsers::ListOfUsers[i]->getUsername())
            {
                this->SendBool(index, true);
                okay = true;
                ID = i;
                break;
            }
        }
        if(okay == false)
            return false;

        this->GetString(index, password);
        if (AllUsers::ListOfUsers[ID]->getPassword() == password)
            this->SendBool(index, true);
        else
        {
            this->SendBool(index, false);
            return false;
        }
        for (int i = 0; i < AllFiles::ListofFiles.size(); i++)//
        {
            if(AllFiles::ListofFiles[i]->getUploader() == username)
             this->SendString(index, AllFiles::ListofFiles[i]->getDenumire());
        }
        this->SendString(index, "end");

        for (int i = 0; i < AllFiles::ListofFiles.size(); i++)
        {
            std::string individualUsername = "";
            int size = AllFiles::ListofFiles[i]->getUsernames().size();

            for (int j = 0; j < size; j++)
            {
                if (individualUsername == "done")
                    break;

                if (AllFiles::ListofFiles[i]->getUsernames()[j] == ',')
                {
                    if (individualUsername == username)
                    {
                        this->SendString(index, AllFiles::ListofFiles[i]->getDenumire());
                        individualUsername = "";
                        break;
                    }
                }
                else
                    individualUsername += AllFiles::ListofFiles[i]->getUsernames()[j];
            }
        }

        std::string rank = AllUsers::ListOfUsers[ID]->getRank();
        this->SendString(index, rank);
        this->SendInt(index, ID);
        this->SendBool(index, true);

        for (int i = 0; i < AllFiles::ListofFiles.size(); i++)
        {
            if (hasPrivilage(username, AllFiles::ListofFiles[i]->getUsernames()))
                this->SendString(index, AllFiles::ListofFiles[i]->getDenumire());
        }

        this->SendString(index, "done");

        break;
    }
    case P_Signup:
    {
        //AllUsers* allusers = new AllUsers();
        std::string username;
        std::string password;
        int ID = lastID;

        this->GetString(index, username);
        for (int i=0;i<AllUsers::ListOfUsers.size();i++)
        {
            if (!verifyUsername(username, AllUsers::ListOfUsers[i]->getUsername()))
            {
                this->SendBool(index, false);
                std::cout << "Username already registered"<< std::endl;
                return false;
            }
        }
        this->SendBool(index, true);

        if (this->GetString(index, password))
            this->SendBool(index, true);
        else
        {
            this->SendBool(index, false);
            return false;
        }

        if (this->SendInt(index, ID))
            this->SendBool(index, true);
        else
        {
            this->SendBool(index, false);
            return false;
        }

        bd->executeQuery(INSERT, new User(username, password, "User", ID));
        //users.push_back(new User(username, password, "client", ID));
        AllUsers::ListOfUsers.push_back(new User(username, password, "User", ID));
        //users[lastID]->execQuery(INSERT);
        lastID++;
        this->SendString(index, "done");
        //user.execQuery(INSERT);
        break;
    }
    case P_Remove:
    {
        int ID;
        this->GetInt(index, ID);

        while (1 != 0)
        {
            string filename;
            this->GetString(index, filename);
            if (filename != "end")
            {
                bd->executeQuery(STERGERE, filename, AllUsers::ListOfUsers[ID]->getUsername());

                std::string filepath = "E:\\Files\\" + filename;

                int status = remove(filepath.c_str());

                if (status == 0)
                {
                    std::cout << "Successfully deleted file " << filename << std::endl;
                }
                else
                    std::cout << "Cannot delete file " << filename << std::endl;
            }
            else
            {
                break;
            }

        }
        break;
    }
    default:
        std::cout << "Unrecognized packet: " << packetType << std::endl;
        std::cout << "Lost contact with client: id = " << index << std::endl;
        instance->CloseConnection(index);
        break;
    }

    return true;
}


bool Server::CloseConnection(int index)
{
    if (closesocket(Connections[index]) == SOCKET_ERROR)
    {
        std::cout << "Failed closing. Error: " << WSAGetLastError() << std::endl;
        return false;
    }

    return true;
}

bool Server::ListenForNewConnection()
{
    SOCKET clientSocket = INVALID_SOCKET;
    clientSocket = accept(ListenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ListenSocket);
        WSACleanup();
        return false;
    }

    else//connection was succesful
    {
        std::cout << "Client connected" << std::endl;
        Connections[ConnectionCounter] = clientSocket;

        connectionThreads[ConnectionCounter] = std::thread(ClientHandler, ConnectionCounter);
        ConnectionCounter++;
        return true;
    }

}

void Server::loadUsers()
{
   // SQLQuery* query = new SelectQuery();
    bd->executeQuery(SELECT);
    this->lastID = AllUsers::ListOfUsers.size();

    std::cout << this->lastID << " users loaded" << std::endl;
}

void Server::ClientHandler(int index)
{
    PACKET packetType;
    while (true)
    {
        if (!instance->GetPacketType(index, packetType))
            break;
        if (!instance->ProcessPacket(index, packetType))
            break;
    }
    //handleClient()
    std::cout << "Lost contact with client: id = " << index << std::endl;
    instance->CloseConnection(index);
}

Server::~Server()
{
    this->instance = nullptr;
}
