#pragma once
#include "IFile.h"
class File
{
private:
    string denumire;
    string usernames;
    int IdFile;
    string uploader;
public:
    string getUsernames() { return usernames; };
    string getDenumire() { return denumire; };
    int getIdFile() { return IdFile; };
    string getUploader() { return uploader; };
    File(string filename, string username,string WhoUploaded);
};

