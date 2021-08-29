#pragma once
#include<iostream>
#include<vector>
using namespace std;
class AllUsers
{
private:
	static int nrID;
public:
	static vector<string> Users;
	int getInt() { return nrID; };
	static void setNrID(int x) { nrID = x; };
};

