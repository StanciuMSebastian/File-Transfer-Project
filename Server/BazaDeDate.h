#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"Enums.h"
#include <windows.h>
#include <stdlib.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <iostream>
#include<string>
#include<vector>
using namespace std;

class IUser;
class AllUsers;
class File;
class AllFiles;

class BazaDeDate
{
protected:
	SQLHANDLE SQLEnvHandle = NULL;
	SQLHANDLE SQLConnectionHandle = NULL;
	SQLHANDLE SQLStatementHandle = NULL;
	SQLRETURN retCode = 0;
public:
	BazaDeDate() { ; }
	void executeQuery(SQLQueryType type, int id, string new_password);
	void executeQuery(SQLQueryType type,IUser* client);
	void executeQuery(SQLQueryType type);
	void executeQuery(SQLQueryType type, File* file);
	void executeQuery(SQLQueryType type, string filename,string uploader);
	
};

