#include "SelectFilesQuery.h"
void SelectFilesQuery::showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
		// Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information
		cout << "SQL driver message: " << message << "\nSQL state: " << SQLState << "." << endl;
}
void SelectFilesQuery::ExecuteQueryFiles()
{


	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
		// Allocates the environment
		return;

	if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		// Sets attributes that govern aspects of environments
		return;

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
		// Allocates the connection
		return;

	if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
		// Sets attributes that govern aspects of connections
		return;
	char SQLQuery[] = "SELECT * FROM Fisiere";
	SQLCHAR retConString[1024]; // Conection string
	switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server Native Client 11.0};SERVER=localhost;DATABASE=File-Sharing;Trusted_Connection=yes;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
		// Establishes connections to a driver and a data source
	case SQL_SUCCESS:
		break;
	case SQL_SUCCESS_WITH_INFO:
		break;
	case SQL_NO_DATA_FOUND:
		showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
		retCode = -1;
		break;
	case SQL_INVALID_HANDLE:
		showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
		retCode = -1;
		break;
	case SQL_ERROR:
		showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
		retCode = -1;
		break;
	default:
		break;
	}

	if (retCode == -1)
		return;

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
		// Allocates the statement
		return;

	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS)) {
		// Executes a preparable statement
		showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
		return;
	}

	else {
		int ID = 0;
		char denumire[256];
		char usernames[256];
		char uploader[256];
		//int i = 0;
		while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
			// Fetches the next rowset of data from the result
			//SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &row, sizeof(int), NULL);
			SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &denumire, sizeof(denumire), NULL);
			SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &usernames, sizeof(usernames), NULL);
			SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &uploader, sizeof(uploader), NULL);


			/*users[i]->setUsername(username);
			v[i]->setPassword(passwd);
			v[i]->setRank(rol);*/

			files.getAll(ID, denumire, uploader,usernames);
			// Retrieves data for a single column in the result set
			//cout << row << " " << username << " " << passwd << " " << rol << endl;
			//i++;
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	//getchar();
}