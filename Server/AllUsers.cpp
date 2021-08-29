#include "AllUsers.h"
#include "User.h"
vector<User*> AllUsers::ListOfUsers = {};
void AllUsers::setAll(string username,string pass,string rol,int ID)
{
    /*User* user=new User(username,pass,rol,-1);
    ListOfUsers.push_back(*user);*/
    ListOfUsers.push_back(new User(username, pass, rol, ID));
    
}