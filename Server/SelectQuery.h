
#pragma once
#include "BazaDeDate.h"
#include "AllUsers.h"
class SelectQuery :
    public BazaDeDate
{
private:
	AllUsers users;
public:
	SelectQuery() { ; };
	void ExecuteQuery() ;
	void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
};

