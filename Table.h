#ifndef TABLE_H
#define TABLE_H

#include "MySQL.h"
#include "BluePrint.h"

#include <string>
#include <vector>
#include <typeinfo>

#include <map>
#include <iostream>
#include <tuple>

#include "BluePrintDataType.h"
#include "ColumnInfo.h"

#include "cppconn/prepared_statement.h"


namespace EZSQL
{
    
class MySQL;
//class BluePrint;

class Table
{
public:
    Table(const std::string tableName, MySQL *msql);
    ~Table();
	std::string getName() {return _name;}
    std::string listRows();
    void addColumn(const std::string &rowName, sqltypes type, int varcharsize = 0);
	void listColumns();
	
    size_t size() { std::cout << "Columns: " << _columns.size() << std::endl; return _columns.size();}
	// vew easy template to see if worked.
	void debugTemplate(const std::string name);
    
    
    //template <class C, typename T>
    //T getPointerType(T C::*v);
    
    template<typename T, typename T2, typename T3>
    void mess(T valueType, T2 theClass, T3 theMember)
    {
        BluePrintDataType<T3> mdata(theMember);
        
        //std::cout << theClass.*theMember << std::endl;
        std::cout << theClass.*mdata.memberPointer << std::endl;
        //std::cout << typeid(decltype(theMember)).name() << std::endl;
        //std::cout << typeid(decltype(getPointerType(theMember))).name() << std::endl;
        //T hello = valueType;
        //std::get<0>(store);
        
        //if(hello == 1){
            //std::cout << "Member value = " << theClass.*data.memberPointer << std::endl;
            //T2 = std::get<1>(store);
        //}
    }
    
    template<typename T, typename T2, typename ...Args>

    void addTemplate(std::string name, std::initializer_list<T> il, T2 Value, Args... args)
	{
		std::cout << "BluePrint name: " << name << std::endl;
		_currentSaveName = name;
		_columnNameInit.clear();
		_columnNameInit.insert(_columnNameInit.end(), il.begin(), il.end());
		
        if(_columnNameInit.size() == 0){
			std::cout << "You have to incude at least 1 column name" << std::endl;
			return; /// a listed description didnt match the database name for variable.
		}
		if(!checkListToTableMembers()){
			std::cout << "SQL Rows Name didnt match our provided names" << std::endl;
			return; /// a listed description didnt match the database name for variable.
		}
		
		_blueprints.emplace(name, BluePrint(_sql, _name));
		_columnNameInitCurrentIndex = 0;
		BluePrintDataType<T2> *bp = new BluePrintDataType<T2>(Value);
		_blueprints[name].addTag(_columnNameInit[0], sqltypes::VARCHAR, (BluePrintDataType_Base*)bp);
		_columnNameInitCurrentIndex++;
		std::cout << "Adding tag." << std::endl;
        //std::cout << theClass.*theMember << std::endl;
       // std::cout << "What" << mdata.memberPointer << std::endl;
		//std::cout << "What1: " << typeid(decltype(Value)).name() << std::endl;
		//BluePrint::addTag()
		//_blueprints[name] = BluePrint(_sql, namelist[0]);
		// m0.insert(std::pair<std::string, Food>("Key", Food("Ice Cream")));
		
		addTemplate(args...);
	}
	
	template<typename T, typename ...Args>
	void addTemplate(T Value, Args... args)
	{
		BluePrintDataType<T> *bp = new BluePrintDataType<T>(Value);
		_blueprints[_currentSaveName].addTag(_columnNameInit[_columnNameInitCurrentIndex], sqltypes::VARCHAR, (BluePrintDataType_Base*)bp);
		_columnNameInitCurrentIndex++;
		std::cout << "Adding tag." << std::endl;
		//std::cout << "Valuetype: " << typeid(decltype(Value)).name() << std::endl;
		addTemplate(args...);
	}
	
    
    /// sets the name of the save templated we're gonna work with.
    /// the next template function called is the one that only takes a value and arguments
    /// it assumes there is
    template<typename T, typename ...Args>
    void Insert(std::string SaveName, T value, Args... args){
        
        auto it = _magic.find(SaveName);
        if(it == _magic.end()){
            /// no template saved by that name
            return;
        }
        _currentTemplate = &it->second;
        _currentSaveName = SaveName;
        
        Insert(args...);
    }
	
	
	template<typename T, typename T2>
	bool Save(T name, T2 tclass)
	{
		
		auto it = _blueprints.find(name);
		if( it == _blueprints.end() ){
			return false;
		}
		
		int length = (*it).second.Tags.size();
		std::shared_ptr<sql::PreparedStatement> statement = (*it).second.getSaveStatement();
		
		std::cout << "Length" << length << std::endl;
		
		auto tpl = it->second.Tags[0];
		//for(int i = 0; i < (*it).second.Tags.size(); i++){
		//	std::cout << "Hello" << std::endl;
		//}
		//std::cout << theClass.*theMember << std::endl;
		
		/*
		for(int i = 0; i < it->second.Tags.size(); i++){
			std::string mname = std::get<0>(it->second.Tags[i]);
			sqltypes mtype = std::get<1>(it->second.Tags[i]);
			switch(mtype){
				case sqltypes::INTEGER:
					//BluePrintDataType_Base* p = (BluePrintDataType*)std::get<2>(it->second.Tags[i]);
					//statement->setInt( i+1, tclass.*p );
					break;
				case sqltypes::VARCHAR:
					//statement->setString(i+1, tclass.*std::get<2>(it->second.Tags[i]));
				break;
			}
		}*/
		statement->execute();
		return true;
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
    /// add a Save class blueprint... templates
	bool checkListToTableMembers();
	
	
    void addSaveClass() { }
    void Insert(){ }
    void addTemplate(){ }
        
    template<typename T, typename ...Args>
    void Insert(T value, Args... args){
        std::cout << "Current Save Name: " << _currentSaveName << " : " << value << std::endl;
        Insert(args...);
    }
	
    std::vector<std::string> _columnNameInit;
	int _columnNameInitCurrentIndex;
    std::vector<ColumnInfo> _columns;
	std::map<std::string, std::vector<std::string> > _magic;
	std::map<std::string, BluePrint> _blueprints;
	
    //std::map<std::string, std::vector<std::tuple<
    bool _isValid;
	std::string _name;
    MySQL *_sql;
    std::string _currentSaveName;
    std::vector<std::string> *_currentTemplate;
	BluePrint* _currentBluePrint;
	
};
}
#endif // TABLE_H
