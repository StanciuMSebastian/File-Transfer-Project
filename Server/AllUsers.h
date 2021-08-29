#pragma once
#include<vector>
#include<iostream>
using namespace std;
class User;
class AllUsers
{
private:
    int ID=0;
public:
    AllUsers() { ; };
    static vector<User*> ListOfUsers;
    void setAll(string username, string pass, string rol, int ID);
    static vector<User*> getVector() { return ListOfUsers; }; //redundat; poti sa folosesti direct ListOfUsers
};


