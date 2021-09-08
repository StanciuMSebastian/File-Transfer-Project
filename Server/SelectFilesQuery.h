#pragma once
#include "BazaDeDate.h"
#include"AllFiles.h"
class SelectFilesQuery :
    public BazaDeDate
{
private:
	AllFiles files;
public:
	SelectFilesQuery() { ; };
	void ExecuteQueryFiles();
	void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
};

