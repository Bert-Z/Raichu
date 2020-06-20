#pragma once

#include <unordered_map>
#include <string>
#include <memory>

namespace raichu
{
    class db
    {
    private:
        using kvmap = std::unordered_map<std::string, std::string>;
        using ptr = std::unique_ptr<kvmap>;
        /* data */
        ptr kv;

    public:
        db() : kv(new kvmap) {}

        void dbPut(const std::string key, const std::string value);
        const std::string &dbRead(const std::string key);
        void dbDelete(const std::string key);
    };
} // namespace raichu
