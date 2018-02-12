#ifndef BLUEPRINTDATATYPE_H
#define BLUEPRINTDATATYPE_H

#include <string>
#include "ColumnInfo.h"
#include <type_traits>
#include <cstdint>

namespace EZSQL
{
    class BluePrintDataType_Base{
    public:
        virtual ~BluePrintDataType_Base() {}
    };
    
    template <class T>
    
    class BluePrintDataType : BluePrintDataType_Base{
    public:
        BluePrintDataType(T mp) : memberPointer(mp){
            /*
            if(std::is_same<T2, std::string>::value){
                CLASSTYPE = cvartypes::String;
            }
            else if(std::is_same<T2, int32_t)::value){
                CLASSTYPE = cvartypes::Int;
            }*/
        }
        ~BluePrintDataType() {}
        T memberPointer;
        sqltypes SQLTYPE;
        cvartypes CLASSTYPE;
    };
}
#endif // BLUEPRINTDATATYPE_H
