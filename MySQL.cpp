#include "MySQL.h"
#include <iostream>

using namespace std;

namespace EZSQL
{

MySQL::MySQL(const std::string &hostName, const std::string &user, const std::string &pw, const std::string &database) :
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
	setupTypeTable();
}

MySQL::~MySQL()
{

}

void MySQL::setupTypeTable()
{
    _typetable["char"] = sqltypes::CHAR;
    _typetable["varchar"] = sqltypes::VARCHAR;
    _typetable["tinytext"] = sqltypes::TINYTEXT;
    _typetable["text"] = sqltypes::TEXT;
    _typetable["blob"] = sqltypes::BLOB;
    _typetable["mediumtext"] = sqltypes::MEDIUMTEXT;
    _typetable["mediumblob"] = sqltypes::MEDIUMBLOB;
    _typetable["longtext"] = sqltypes::LONGTEXT;
    _typetable["longblob"] = sqltypes::LONGBLOB;
    _typetable["enum"] = sqltypes::ENUM;
    _typetable["set"] = sqltypes::SET;
    _typetable["tinyint"] = sqltypes::TINYINT;
    _typetable["smallint"] = sqltypes::SMALLINT;
    _typetable["mediumint"] = sqltypes::MEDIUMINT;
    _typetable["int"] = sqltypes::INTEGER;
    _typetable["bigint"] = sqltypes::BIGINT;
    _typetable["float"] = sqltypes::FLOAT;
    _typetable["double"] = sqltypes::DOUBLE;
    _typetable["decimal"] = sqltypes::DECIMAL;
    _typetable["date"] = sqltypes::DATE;
    _typetable["datetime"] = sqltypes::DATETIME;
    _typetable["timestamp"] = sqltypes::TIMESTAMP;
    _typetable["time"] = sqltypes::TIME;
    _typetable["year"] = sqltypes::YEAR;
    
    //enum sqltypes{
   // VARCHAR, CHAR, TINYTEXT, TEXT, BLOB, MEDIUMTEXT,
   // MEDIUMBLOB, LONGTEXT, LONGBLOB, ENUM, SET, TINYINT,
   // SMALLINT, MEDIUMINT, INT, BIGINT, FLOAT, DOUBLE, DECIMAL,
    //DATE, DATETIME, TIMESTAMP, TIME, YEAR
}



void MySQL::printError(sql::SQLException &e)
{
  cout << "# ERR: SQLException in " << __FILE__;
  cout << "(" << __FUNCTION__ << ") on line "
     << __LINE__ << endl;
  cout << "# ERR: " << e.what();
  cout << " (MySQL error code: " << e.getErrorCode();
  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}


bool MySQL::isConnected()
{
    /// work on this later
    return true;
}

bool MySQL::loadTable(const std::string &tableName)
{
    std::string statement = "SELECT column_name,";
        statement += "column_type FROM information_schema.columns WHERE ";
        statement += "table_name='" + tableName + "'";
    
    try
    {
        sql::Statement *stmnt =  _con->createStatement();
        sql::ResultSet *results = stmnt->executeQuery(statement);
        Table* table = new Table(tableName, this);
        while( results->next() ){
            //cout << results->getString(1) << endl;
            //cout << results->getString(2) << endl;
            auto rtype = getSQLType(results->getString(2));
            table->addColumn(results->getString(1), std::get<0>(rtype), std::get<1>(rtype));
        }
        
        if(table->size() == 0){
            //cout << "Deleting table" << endl;
            delete table;
        }
        else{
            //cout << "Pushed back table" << endl;
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

Table* MySQL::getTable(const std::string &tableName)
{
	for(size_t i = 0; i < _tables.size(); i++){
		if(_tables[i]->getName() == tableName)
			return _tables[i];
	}
	return 0;
}

std::tuple<sqltypes, int> MySQL::getSQLType(std::string typeinfo)
{
    std::string::size_type pos = typeinfo.find('(');
    std::string::size_type pos2 = typeinfo.find(')');
    std::string t = typeinfo.substr(0,pos);
    std::string s2 = typeinfo.substr(pos+1, (pos2 - pos - 1));
    sqltypes mtype = _typetable[t];
    return make_pair(mtype, stoi(s2));
}

}  // namespace