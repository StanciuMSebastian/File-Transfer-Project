#pragma once
#include "IUser.h"

class User:public IUser
{
private:
	std::string username;
	std::string password;
	std::string rank = "User";
	int ID=0;
public:
	void setUsername(std::string username)override { this->username = username; };
	std::string getUsername() override { return this->username; };

	void setPassword(std::string password)override { this->password = password; };
	std::string getPassword() { return this->password; };

	void setRank(std::string rank) override { this->rank = rank; };
	std::string getRank()override { return this->rank; };
	
	void setID(int ID)override { this->ID = ID; };
	int getID()override { return this->ID; };
	User(std::string username, std::string password, std::string rank, int ID);
};

