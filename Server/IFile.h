#pragma once
#include<iostream>
#include<vector>
using namespace std;
class IFile
{
public:
	virtual string getFileName() = 0;
	virtual string getusername() = 0;
	virtual int getID() = 0;
	virtual string getWhoUploaded() = 0;
};