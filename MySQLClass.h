#ifndef MYSQLCLASS_H
#define MYSQLCLASS_H

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <string>
#include <iostream>
#include <string.h>
#include <vector>
#include <memory>


#include <Mysqltable.h>

class MYSQLTable;

class MySQLClass
{
public:
	MySQLClass(const std::string &hostName, const std::string &user, const std::string &pw, const std::string &database);
	~MySQLClass();
	bool isConnected();
    bool loadTable(const std::string &tableName);
    MYSQLTable* getTable(const std::string &tableName);
private:
	std::string _databaseName, _hostName, _user, _pw;
    std::vector<MYSQLTable*> _tables;

	void printError(sql::SQLException &e);

	sql::Driver *driver;
	std::unique_ptr< sql::Connection > _con;
};

#endif // MYSQLCLASS_H
