#ifndef MYSQLTABLE_H
#define MYSQLTABLE_H

#include <string>
#include <vector>

#include <MySQLClass.h>
#include "ColumnInfo.h"
#include <map>

class MySQLClass;

class MYSQLTable
{
public:
    MYSQLTable(const std::string &tableName, MySQLClass* _sql);
    ~MYSQLTable();
	std::string getName() {return _name;}
    void addColumn(const std::string &rowName, const std::string &typeName);
    size_t size() {return _columns.size();}
	// vew easy template to see if worked.
	void debugTemplate(const std::string &name);
	// add "easy template" stores by name which values you wish to update, so we dont have to specify each time.
	template<typename T>
	void addEasyTemplate(T v){
		return;
	}
	template<typename T, typename ... Args>
	void addEasyTemplate(T first, Args... args) {
		_magic[first].push_back(args...);
		addEasyTemplate(first, args...);
		return;
	}
	
	// update an entire record/row in SQL.  give column name, primary key of row to update, 
	// and then the new values in exactly the of the rows.
	/*
	template<typename First, typename Second, typename ... Strings>
	void updateValue(First arg, tconst Strings&... rest) {
		std::cout<<arg<<" ";
		updateValue(rest...);
	}*/
private:
    std::vector<ColumnInfo> _columns;
	std::map<std::string, std::vector<std::string> > _magic;
    bool _isValid;
	std::string _name;
    MySQLClass *_sql;
};

#endif // MYSQLTABLE_H
