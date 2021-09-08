#pragma once

#include "BazaDeDate.h"
class InsertQuery :
    public BazaDeDate
{
private:
	string nume;
	string parola;
	string rank;
	int id;
public:

	InsertQuery(string nume, string parola, string rank, int id)
	{
		this->nume = nume;
		this->parola = parola;
		this->rank = rank;
		this->id = id;
	}
	 string getUsername() { return nume; };
	 string getPassword() { return parola; };
	 string getRank() { return rank; };
	 int getID() { return id; };
	 void ExecuteQuery();
	 void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
};

