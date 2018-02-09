#ifndef COLUMNINFO_H
#define COLUMNINFO_H

#include <string>

enum sqltypes{
    varchar, bigint, integer, smallint, boolean
};

class ColumnInfo
{
public:
    void setType() {}
    std::string _name;
    int _varcharsize;
    sqltypes _sqltype;
};

#endif // COLUMNINFO_H
