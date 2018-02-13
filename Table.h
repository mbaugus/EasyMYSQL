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
    size_t size() { std::cout << "Columns: " << _columns.size() << std::endl; return _columns.size();}
	// vew easy template to see if worked.
	void debugTemplate(const std::string name);
    
    
	template<typename T>
	void addSaveTemplate(std::string Name, std::initializer_list<T> il){
        auto it = _magic.find(Name);
        std::cout << "Create some" << std::endl;
        if(it == _magic.end()){
            std::cout << "Create some stuff" << std::endl;
            std::vector<std::string> v;
            _magic[Name] = v;
        }
        it = _magic.find(Name);
        
        for(auto i = il.begin(); i != il.end(); ++i){
            it->second.push_back((*i));
        }
    }
    
    //template <class C, typename T>
    //T getPointerType(T C::*v);
    
    template<typename T, typename T2, typename T3>
    void mess(T valueType, T2 theClass, T3 theMember)
    {
       // struct BluePrintDataType;
        BluePrintDataType<T3> mdata(theMember);
        
        //BluePrint bp(_sql->getConnection(), "Room");
        //bp.addTag("Fox", sqltypes::VARCHAR);
        //bp.addTag("Hen", sqltypes::VARCHAR);
        //bp.addTag("Lego", sqltypes::VARCHAR);
        
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
    
    template<typename T>
    void messier(T value)
    {
        
    }
	
	
	void addTemplate(){}
    template<typename T, typename T2, typename ...Args>
   // void addTemplate("RoomSave",
    //      {"Description", "Holiday", "Flippy"},
    //      &Test::a, &Test::b, &Test::c);
    void addTemplate(std::string name, std::initializer_list<T> il, T2 Value, Args... args)
	{
		std::cout << "BluePrint name: " << name << std::endl;
		_currentSaveName = name;
		if(!checkListToTableMembers(il)){
			std::cout << "SQL Rows Name didnt match our provided names" << std::endl;
			return; /// a listed description didnt match the database name for variable.
		}
		std::cout << typeid(decltype(Value)).name() << std::endl;
		addTemplate(args...);
	}
	template<typename T, typename ...Args>
	void addTemplate(T Value, Args... args)
	{
		std::cout << typeid(decltype(Value)).name() << std::endl;
		addTemplate(args...);
	}
	
    
   // We want to Register a member variable with a blueprint name.  
    //example, ("SavePlayer", Player::name);  we need to pass the 
    // ("SavePlayer", &Player::name, )

    
    template<typename T, typename ...Args>
    void addSaveClass(std::string templateName, T value, Args... args)
    {
        //auto it = _SaveClassBluePrints.find(templateName);
       // if(it != _SaveClassBluePrints.end()){
            /// already template saved by that name
         //   return;
        //}
    }
    
    
    
    /// save class from a blueprint ...templates
    template<typename T>
    void saveClass(std::string templateName, T& classReference)
    {
        
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
	template<typename T>
	bool checkListToTableMembers(std::initializer_list<T> il)
	{
		for(auto i = il.begin(); i != il.end(); ++i){
			bool found = false;
			for(int x = 0; x < _columns.size(); x++){
				if( (*i) == _columns[x]._name){
					found = true;
					std::cout << (*i) << std::endl;
				}
			}
			if(!found){
				return false; /// something was on our descriptor that isn't a column name in SQL.
			}
        }
		
		return true;
	}
	
	
    void addSaveClass() { }
    void Insert(){ }
    
        
    template<typename T, typename ...Args>
    void Insert(T value, Args... args){
        std::cout << "Current Save Name: " << _currentSaveName << " : " << value << std::endl;
        Insert(args...);
    }

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
