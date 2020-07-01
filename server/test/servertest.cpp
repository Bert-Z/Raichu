#include "../datanode/dbservice/dbservice.h"
#include <iostream>

int main()
{
    std::unique_ptr<raichu::server::dbservice> dbs(new raichu::server::dbservice(3));
   
    return 0;
}
