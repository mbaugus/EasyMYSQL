#include "BluePrint.h"
#include <iostream>

#include "MySQL.h"

using namespace std;

namespace EZSQL
{

BluePrint::BluePrint(MySQL* msql, std::string name) : 
_sql(msql), 
doesStatementNeedBuilt(false),
_tableName(name),
_matchTag("id")
{
    
}

BluePrint::~BluePrint()
{
    
}

void BluePrint::setMatchTag(const std::string matchTo)
{
    _matchTag = matchTo;
    doesStatementNeedBuilt = true;
}
void BluePrint::addTag(std::string name, sqltypes sqltype, BluePrintDataType_Base*  data)
{
    Tags.push_back(std::make_tuple(name, sqltype, data));
    doesStatementNeedBuilt = true;	
    //rebuildStatements();
}

void BluePrint::rebuildStatements()
{
    std::string savestmnt;
    savestmnt.reserve(1000);
    std::string tempstring = "";
    int n = Tags.size();

    savestmnt = "UPDATE " + _tableName + " SET";
    for(int i = 0; i < n; i++){
        tempstring = std::get<0>(Tags[i]);
        if(tempstring != _matchTag){
            savestmnt += " " + tempstring + " = (?)";
            if(i != n - 1){
                savestmnt += ",";
            }
        }
    }
    savestmnt += " WHERE " + _matchTag + " = (?)";
    cout << savestmnt << endl;
    
    _savestatement.reset(_sql->getConnection()->prepareStatement(savestmnt));

}

std::shared_ptr<sql::PreparedStatement> BluePrint::getSaveStatement()
{
	if(doesStatementNeedBuilt)
		rebuildStatements();
		
    return _savestatement;
}

std::shared_ptr<sql::PreparedStatement> BluePrint::getLoadStatement()
{
	if(doesStatementNeedBuilt)
		rebuildStatements();
		
    return _loadstatement;
}

std::shared_ptr<sql::PreparedStatement> BluePrint::getNewStatement()
{
	if(doesStatementNeedBuilt)
		rebuildStatements();
		
    return _newstatement;
}

}