#ifndef MYSQLTABLE_H
#define MYSQLTABLE_H

#include <string>
#include <MySQLClass.h>
#include "ColumnInfo.h"

class MySQLClass;

class MYSQLTable
{
public:
    MYSQLTable(const std::string &tableName, MySQLClass* _sql);
    ~MYSQLTable();
    void addColumn(const std::string &rowName, const std::string &typeName);
    size_t size() {return _columns.size();}
    bool changeValue(const std::string &column,const std::string &value);
    bool changeValue(const std::string &column, const int value);
    bool changeValue(const std::string &column, const bool value);

private:
    std::vector<ColumnInfo> _columns;
    bool _isValid;
    MySQLClass *_sql;
};

#endif // MYSQLTABLE_H
