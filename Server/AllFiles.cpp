#include "AllFiles.h"
#include"File.h"
vector<File*> AllFiles::ListofFiles = {};
void AllFiles::getAll(int ID, string denumire, string uploader,string usernames)
{
    /*User* user=new User(username,pass,rol,-1);
    ListOfUsers.push_back(*user);*/
    File* newFile = new File(denumire, usernames, uploader);
    ListofFiles.push_back(newFile);

}

void AllFiles::deleteFile(string numeFisier, string Uploader)
{
    for (int i = 0; i < ListofFiles.size(); i++)
    {
        if (ListofFiles[i]->getDenumire() == numeFisier && ListofFiles[i]->getUploader() == Uploader)
        {
            ListofFiles.erase(ListofFiles.begin() + i);
            break;
        }
    }
}