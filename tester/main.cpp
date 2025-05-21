#include <iostream>
#include "json_serialize.h"
#include "param_serialize.h"

class Test
{
public:
    std::string String;
    float Float;
    bool Bool;
    double Double;
    int8_t Int8;
    int16_t Int16;
    int32_t Int32;
    int64_t Int64;
    uint8_t UInt8;
    uint16_t UInt16;
    uint32_t UInt32;
    uint64_t UInt64;
    std::vector<int> Array;
    std::set<int> Set;
    std::list<int> List;
};

REGIST_MEMBER_JSON(
    Test, 
    NICK(String,string),
    NICK(Float,float),
    NICK(Bool,bool),
    NICK(Double,double),
    NICK(Int8,int8),
    NICK(Int16,int16),
    NICK(Int32,int32),
    NICK(Int64,int64),
    NICK(UInt8,uint8),
    NICK(UInt16,uint16),
    NICK(UInt32,uint32),
    NICK(UInt64,uint64),
    NICK(Array,array),
    NICK(Set,set),
    NICK(List,list)
);

REGIST_MEMBER_PARAM(
    Test,
    NICK(String,string),
    NICK(Float,float),
    NICK(Bool,bool),
    NICK(Double,double),
    NICK(Int8,int8),
    NICK(Int16,int16),
    NICK(Int32,int32),
    NICK(Int64,int64),
    NICK(UInt8,uint8),
    NICK(UInt16,uint16),
    NICK(UInt32,uint32),
    NICK(UInt64,uint64)
);

int main()
{
    Test t;
    t.String = "std::string";
    t.Float = 3.14;
    t.Bool = true;
    t.Double = 3.1415926;
    t.Int8 = -127;
    t.Int16 = -32760;
    t.Int32 = -210000000;
    t.Int64 = -8000000000;
    t.UInt8 = 255;
    t.UInt16 = 65535;
    t.UInt32 = 4200000000;
    t.UInt64 = 80000000000;
    t.Array = {1, 2, 3};
    t.Set = {4, 5, 6, 7};
    t.List = {8, 9, 10};

    auto json = serialize::JsonSerializer<Test>::ToString(t);
    std::cout << "json =  " << json << std::endl;

    auto params = serialize::ParamSerializer<Test>::ToString(t);
    std::cout << "params = " << params << std::endl;

    Test t2 = serialize::JsonSerializer<Test>::FromString(json);
    std::cout << "t2.String = " << t2.String << std::endl;

    Test t3 = serialize::ParamSerializer<Test>::FromString(params);
    std::cout << "t3.String = " << t3.String << std::endl;

    std::shared_ptr<Test> t4 = serialize::JsonSerializer<Test>::FromStringPtr(json);
    auto json4 = serialize::JsonSerializer<Test>::ToString(t4);
    std::cout << "json4 = " << json4 << std::endl;

    std::shared_ptr<Test> t5 = serialize::ParamSerializer<Test>::FromStringPtr(params);
    auto param5 = serialize::ParamSerializer<Test>::ToString(t5);
    std::cout << "param5 = " << param5 << std::endl;


    return 0;
}

