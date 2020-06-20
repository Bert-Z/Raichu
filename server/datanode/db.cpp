#include "db.h"

namespace raichu
{
    void db::dbPut(const std::string key, const std::string value)
    {
        (*kv)[key] = value;
    }

    const std::string &db::dbRead(const std::string key)
    {
        return (*kv).at(key);
    }

    void db::dbDelete(const std::string key)
    {
        (*kv).erase(key);
    }
} // namespace raichu