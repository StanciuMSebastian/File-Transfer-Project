#pragma once
#include "BazaDeDate.h"
#include"AllFiles.h"

class DeleteFiles :
    public BazaDeDate
{
private:
    string NumeFisier;
    string Uploader;
    AllFiles files;
public:
    DeleteFiles(string NumeFisier, string Uploader)
    {
        this->NumeFisier = NumeFisier;
        this->Uploader = Uploader;
    }
    string getNumeFisier() { return this->NumeFisier; };
    string getUploader() { return this->Uploader; };
    void ExecuteQuery();
    void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
};

