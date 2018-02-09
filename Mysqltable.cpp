#include "Mysqltable.h"

#include <MySQLClass.h>

#include <iostream>

using namespace std;

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

void MYSQLTable::debugTemplate(std::string name)
{
	auto v = _magic[name];
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << endl;
	}
}
