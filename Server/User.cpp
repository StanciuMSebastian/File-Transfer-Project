#include "User.h"
User::User(std::string username, std::string password , std::string rank, int ID)
{
	this->username = username; this->password = password;
	this->rank = rank; this->ID = ID;
}
