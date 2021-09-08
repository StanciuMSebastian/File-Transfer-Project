#include "File.h"

File::File(string filename, string uploader,string usernames)
{
	this->denumire = filename;
	this->usernames = usernames;
	this->uploader = uploader;
}
