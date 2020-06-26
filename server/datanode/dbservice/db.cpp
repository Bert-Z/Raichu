#include "db.h"
#include <iostream>

namespace raichu
{
    namespace server
    {
        namespace db
        {
            void db::dbPut(const std::string key, const std::string value)
            {
                kvs[key] = value;
            }

            const std::string db::dbRead(const std::string key)
            {
                if (kvs.find(key) == kvs.end())
                    return key + " not found";

                return kvs.at(key);
            }

            void db::dbDelete(const std::string key)
            {
                kvs.erase(key);
            }

            const int db::dbSize()
            {
                return kvs.size();
            }
        } // namespace db
    }     // namespace server
} // namespace raichu
