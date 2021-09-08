#pragma once
#include<vector>
#include<iostream>
using namespace std;
class File;
class AllFiles
{
private:
    int ID = 0;
public:
    AllFiles() { ; };
    static vector<File*> ListofFiles;
    void getAll(int ID, string denumire, string username,string uploader);
    static vector<File*> getVector() { return ListofFiles; };
    void deleteFile(string numeFisier,string Uploader);
};
