#ifndef MYSQL_H
#define MYSQL_H

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
#include <unordered_map>

#include "Table.h"
#include "ColumnInfo.h"

namespace EZSQL
{
    
class Table;
    
class MySQL
{
public:
	MySQL(const std::string &hostName, const std::string &user, const std::string &pw, const std::string &database);
	~MySQL();
	bool isConnected();
    bool loadTable(const std::string &tableName);
    Table* getTable(const std::string &tableName);
    std::tuple<sqltypes, int> getSQLType(std::string typeinfo);
    /// never store the connection pointer.
    sql::Connection* getConnection() {return _con.get();}
private:
	std::string _databaseName, _hostName, _user, _pw;
    std::vector<Table*> _tables;
    std::unordered_map<std::string, sqltypes> _typetable;
	void printError(sql::SQLException &e);
    void setupTypeTable();
	sql::Driver *driver;
	std::unique_ptr< sql::Connection > _con;
};
}
#endif // MYSQL_H
