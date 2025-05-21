#include <iostream>
#include "json_serialize.h"
#include "param_serialize.h"

class Test
{
public:
    std::string Name;
    float Salary;
    bool Gender;
    int Age;
    std::vector<int> Array;
    std::set<int> Set;
    std::list<int> List;
};
REFLECTION_MEMBER_JSON(
    Test, 
    NICK(Name, name), 
    NICK(Salary, salary),
    NICK(Gender, gender),
    NICK(Age, age),
    NICK(Array, array),
    NICK(Set, set),
    NICK(List, list)
);

REFLECTION_MEMBER_PARAM(
    Test,
    NICK(Name, name), 
    NICK(Salary, salary),
    NICK(Gender, gender),
    NICK(Age, age)
);

int main()
{
    Test t;
    t.Name = "小明";
    t.Salary = 6000.00f;
    t.Gender = true;
    t.Age = 18;
    t.Array = {1, 2, 3};
    auto json = serialize::JsonEntity<Test>::ToString(t);
    std::cout << json << std::endl;

    Test t2 = serialize::JsonEntity<Test>::template FromString<Test>(json);
    std::cout << t2.Name << std::endl;

    auto params = serialize::ParamEntity<Test>::ToString(t);
    std::cout << params << std::endl;

    Test t3 = serialize::ParamEntity<Test>::template FromString<Test>(params);
    std::cout << t3.Name << std::endl;
    return 0;
}

