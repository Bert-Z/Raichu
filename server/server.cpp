#include "datanode/db.h"
#include <iostream>

int main()
{
    std::unique_ptr<raichu::server::db::db> db(new raichu::server::db::db());
    db->dbPut("key1", "value1");
    db->dbPut("key2", "value2");
    std::cout << db->dbRead("key1") << std::endl;
    std::cout << db->dbRead("key3") << std::endl;
    db->dbDelete("key1");
    db->dbDelete("key3");
    std::cout << db->dbRead("key1") << std::endl;
    std::cout << db->dbSize() << std::endl;

    return 0;
}
