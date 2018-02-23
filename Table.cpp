#include "Table.h"

#include <iostream>

using namespace std;

namespace EZSQL
{

Table::Table(const std::string tableName, MySQL* msql)
{
    _name = tableName;
    _sql = msql;
}

Table::~Table()
{
    
}

std::string Table::listRows()
{
    for(int i = 0; i < _columns.size();i++){
		cout << _columns[i]._name << endl;
	}
}

bool Table::checkListToTableMembers()
{
	for(auto i = _columnNameInit.begin(); i != _columnNameInit.end(); ++i){
		bool found = false;
		for(int x = 0; x < _columns.size(); x++){
			if( (*i) == _columns[x]._name){
				found = true;
				//std::cout << (*i) << std::endl;
			}
		}
		if(!found){
			return false; /// something was on our descriptor that isn't a column name in SQL.
		}
	}
	return true;
}

void Table::listColumns()
{
	for(int i = 0; i < _columns.size(); i++)
	{
		std::cout << _columns[i]._name << " " << _columns[i]._sqltype << " " << _columns[i]._varcharsize << std::endl;
	}
}

void Table::addColumn(const std::string &rowName, sqltypes type, int varcharsize /*=0*/)
{
    ColumnInfo ci;
    ci._name = rowName;
    ci._sqltype = type;
    ci._varcharsize = varcharsize;
    _columns.push_back(ci);
}

void Table::debugTemplate(std::string name)
{
	std::vector<std::string> *v =  &_magic[name];

	for(int i = 0;i < (*v).size();i++){
		cout << (*v)[i] << endl;
	}
}

}