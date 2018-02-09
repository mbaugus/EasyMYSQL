#include "Mysqltable.h"

#include <MySQLClass.h>

MYSQLTable::MYSQLTable(const std::string &tableName, MySQLClass* sql)
{
    _sql = sql;
}

MYSQLTable::~MYSQLTable()
{
    
}

void MYSQLTable::addColumn(const std::string &rowName, const std::string &typeName)
{
    
}


bool MYSQLTable::changeValue(const std::string &column,const std::string &value)
{
    
}
bool MYSQLTable::changeValue(const std::string &column, const int value)
{
    
}
bool MYSQLTable::changeValue(const std::string &column, const bool value)
{
    
}
