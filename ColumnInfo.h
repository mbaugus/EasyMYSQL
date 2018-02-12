#ifndef COLUMNINFO_H
#define COLUMNINFO_H

#include <string>

namespace EZSQL
{


enum sqltypes{
    VARCHAR, CHAR, TINYTEXT, TEXT, BLOB, MEDIUMTEXT,
    MEDIUMBLOB, LONGTEXT, LONGBLOB, ENUM, SET, TINYINT,
    SMALLINT, MEDIUMINT, INTEGER, BIGINT, FLOAT, DOUBLE, DECIMAL,
    DATE, DATETIME, TIMESTAMP, TIME, YEAR, BOOLEAN
};

enum cvartypes{
    String, Int, Long, Bool, Float, Double
};

class ColumnInfo
{
public:
    void setType() {}
    std::string _name;
    int _varcharsize;
    sqltypes _sqltype;
};
}
#endif // COLUMNINFO_H
