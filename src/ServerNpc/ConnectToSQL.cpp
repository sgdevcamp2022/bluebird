#include <iostream>
#include "ConnectToSQL.h"

using namespace std;

ConnectToSQL::ConnectToSQL()
{
	ConnPtr = nullptr;
	SQLInit();
}

ConnectToSQL::~ConnectToSQL()
{
	mysql_close(ConnPtr);
}

int ConnectToSQL::SQLInit()
{
	mysql_init(&Conn);
	ConnPtr = mysql_real_connect(&Conn, "127.0.0.1", "root", "Z797944z!", "npcserver", 3306, (char*)NULL, 0);

	if (ConnPtr == NULL)
	{
		cout << "Error : " << mysql_error(&Conn) << endl;
		return 0;
	}
	cout << "Success MySQL Init" << endl;
	return 1;
}

MYSQL_ROW ConnectToSQL::SQLQuery(const char* query)
{
	Stat = mysql_query(ConnPtr, query);
	if (Stat != 0)
	{
		cout << "Error : " << mysql_error(&Conn) << endl;
		return 0;
	}

	Result = mysql_store_result(ConnPtr);
	while ((Row = mysql_fetch_row(Result)) != NULL)
	{
		mysql_free_result(Result);
		return Row;
	}
	
	//cout << Row[0] << endl;
	return 0;
}