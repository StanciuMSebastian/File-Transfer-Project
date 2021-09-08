#pragma once

#include <iostream>
#include <vector>
#include"Enums.h"
class IUser
{
	
public:
	virtual void setUsername(std::string username)=0;
	virtual std::string getUsername()=0;

	virtual void setPassword(std::string password)=0;
	virtual std::string getPassword()=0;

	virtual void setRank(std::string rank)=0;
	virtual std::string getRank()=0;

	virtual void setID(int ID)=0;
	virtual int getID()=0;

};

