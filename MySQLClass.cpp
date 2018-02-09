#include "MySQLClass.h"
#include <iostream>


using namespace std;

MySQLClass::MySQLClass(const std::string &hostName, const std::string &user, const std::string &pw, const std::string &database) :
	_databaseName(database),
	_hostName(hostName),
	_user(user),
	_pw(pw)
{
        try{
	    driver = get_driver_instance();
           _con.reset( driver->connect(_hostName, _user, _pw) );
           _con->setSchema(database);
        }
        catch(sql::SQLException &e){
           printError(e);
        }
        setupDatabase();
}

MySQLClass::~MySQLClass()
{

}

void MySQLClass::printError(sql::SQLException &e)
{
  cout << "# ERR: SQLException in " << __FILE__;
  cout << "(" << __FUNCTION__ << ") on line "
     << __LINE__ << endl;
  cout << "# ERR: " << e.what();
  cout << " (MySQL error code: " << e.getErrorCode();
  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}


bool MySQLClass::isConnected()
{
    /// work on this later
    return true;
}

bool MySQLClass::loadTable(const std::string &tableName)
{
    std::string statement = "SELECT column_name,";
        statement += "column_type FROM information_schema.columns WHERE ";
        statement += "table_name='" + tableName + "'";
    
    try
    {
        sql::Statement *stmnt =  _con->createStatement();
        sql::ResultSet *results = stmnt->executeQuery(statement);
        MYSQLTable* table = new MYSQLTable(tableName, this);
        while( results->next() ){
            cout << results->getString(1) << endl;
            cout << results->getString(2) << endl;
            table->addColumn(results->getString(1), results->getString(2));
        }
        
        if(table->size() == 0){
            delete table;
        }
        else{
            _tables.push_back(table);
        }
        delete results;
        delete stmnt;
    }
        catch(sql::SQLException &e)
    {
       printError(e);
    }
}

MYSQLTable* getLoadedTable(const std::string &tableName)
{
        
}