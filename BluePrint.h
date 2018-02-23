#ifndef BLUEPRINT_H
#define BLUEPRINT_H

#include <string>
#include <vector>
#include <tuple>
#include <memory>

//#include "MySQL.h"
#include "ColumnInfo.h"
#include "BluePrintDataType.h"
#include "cppconn/prepared_statement.h"

namespace EZSQL
{

    
class MySQL;
class BluePrintDataType_Base;

class BluePrint
{
public:
    BluePrint(MySQL* msql, std::string name);
	BluePrint(){}
    ~BluePrint();
    /// this is the tag you will save by on your table.
    ///  such as UPDATE <table> WHERE 'MATCHTO' = 'VALUE' 
    void setMatchTag(const std::string matchTo);
    void addTag(std::string name, sqltypes sqltype, BluePrintDataType_Base* data);
    void rebuildStatements();
    std::shared_ptr<sql::PreparedStatement> getSaveStatement();
    std::shared_ptr<sql::PreparedStatement> getLoadStatement();
    std::shared_ptr<sql::PreparedStatement> getNewStatement();
	std::vector< std::tuple< std::string, sqltypes, BluePrintDataType_Base* > > Tags;
private:
    std::string _tableName;
    std::string _name;
    /// match tag defaults to id
    std::string _matchTag;
    
    std::shared_ptr<sql::PreparedStatement> _savestatement;
    std::shared_ptr<sql::PreparedStatement> _loadstatement;
    std::shared_ptr<sql::PreparedStatement> _newstatement;
    
    bool doesStatementNeedBuilt;
    MySQL *_sql;
};

}

#endif // BLUEPRINT_H
