#include "../datanode/dbservice/dbservice.h"
#include <iostream>

int main()
{
    std::unique_ptr<raichu::server::dbservice> dbs(new raichu::server::dbservice());
    std::cout << dbs->Put("1", "key1", "value1") << std::endl;
    std::cout << dbs->Put("1", "key2", "value2") << std::endl;
    std::cout << dbs->Put("1", "key1", "value2") << std::endl;
    std::cout << dbs->Put("2", "key1", "value2") << std::endl;
    std::cout << dbs->Put("3", "key1", "value2") << std::endl;

    std::vector<std::string> names;
    dbs->getAllNodeName(names);
    for (auto name : names)
        std::cout << name << std::endl;

    dbs->Delete("2", "key1");

    dbs->getAllNodeName(names);
    for (auto name : names)
        std::cout << name << std::endl;

    std::cout << dbs->Read("1", "key1") << std::endl;
    std::cout << dbs->Read("4", "key1") << std::endl;
    std::cout << dbs->Read("1", "key4") << std::endl;

    return 0;
}