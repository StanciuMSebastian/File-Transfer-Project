#pragma once
#include "BazaDeDate.h"
class InsertFiles :
    public BazaDeDate
{
private:
	string denumire;
	string usernames;
	int IdFile;
	string uploader;
public:

	InsertFiles(string denumire, string username,string WhoUploaded)
	{
		this->denumire = denumire;
		this->usernames= username;
		this->uploader = WhoUploaded;
	}
	string getUsernames() { return usernames; };
	string getDenumire() { return denumire; };
	int getIdFile() { return IdFile; };
	string getUploader() { return uploader; };
	void ExecuteQuery();
	void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
};

