#pragma once
#include "BazaDeDate.h"
class UpdateQuery :
    public BazaDeDate
{
private:
    int id;
    string parola_noua;
public:
    UpdateQuery(int id, string parola_noua)
    {
        this->id = id;
        this->parola_noua = parola_noua;
    }
    int getUpdateId() { return this->id; };
    string getParola() { return this->parola_noua; };
    void ExecuteQuery();
    void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
};