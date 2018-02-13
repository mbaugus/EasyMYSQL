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