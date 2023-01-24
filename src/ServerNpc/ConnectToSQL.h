#pragma once
#include <mysql.h>

#pragma comment(lib, "libmySQL.lib")

class ConnectToSQL
{
public:
	ConnectToSQL();
	~ConnectToSQL();

	int SQLInit();

	MYSQL_ROW SQLQuery(const char* query);


private:
	MYSQL Conn;
	MYSQL* ConnPtr;
	MYSQL_RES* Result;
	MYSQL_ROW Row;
	int Stat;
};