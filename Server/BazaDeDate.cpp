#include "BazaDeDate.h"
#include "InsertQuery.h"
#include"InsertFiles.h"
#include"SelectQuery.h"
#include"DeleteFiles.h"
#include"SelectFilesQuery.h"
#include"User.h"
#include"File.h"
#include "UpdateQuery.h"
void BazaDeDate::executeQuery(SQLQueryType type,IUser* client)
{
	switch (type)
	{
	case INSERT:
	{
		InsertQuery query(client->getUsername(), client->getPassword(), client->getRank(),client->getID());
		query.ExecuteQuery();
	}
	default:
		break;
	}
}
void BazaDeDate::executeQuery(SQLQueryType type)
{
	switch (type)
	{
	case SELECT:
	{
		SelectQuery query;
		SelectFilesQuery getfiles;
		query.ExecuteQuery();
		getfiles.ExecuteQueryFiles();
	}
	default:
		break;
	}
}
void BazaDeDate::executeQuery(SQLQueryType type, File* file)
{
	switch (type)
	{
	case INSERT:
	{
		InsertFiles query(file->getDenumire(), file->getUploader(),file->getUsernames());
		query.ExecuteQuery();
	}
	default:
		break;
	}
}
void BazaDeDate::executeQuery(SQLQueryType type, string filename, string uploader)
{
	switch (type)
	{
	case STERGERE:
	{
		DeleteFiles query(filename, uploader);
		query.ExecuteQuery();
	}
	default:
		break;
	}
}

void BazaDeDate::executeQuery(SQLQueryType type, int id, string new_password)
{
	switch (type)
	{
	case UPDATE:
	{
		UpdateQuery query(id, new_password);
		query.ExecuteQuery();
	}
	default:
		break;
	}


}