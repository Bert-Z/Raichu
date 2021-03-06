#pragma once

#include <unordered_map>
#include <string>
#include <memory>

namespace raichu
{
    namespace server
    {
        namespace db
        {
            using kvmap = std::unordered_map<std::string, std::string>;

            class db
            {
            private:
                /* data */
                // For storage
                kvmap kvs;
                // For distinguish
                std::string name;

            public:
                db(const std::string &name) : kvs(), name(name) {}

                void dbPut(const std::string key, const std::string value);

                const std::string dbRead(const std::string key);

                void dbDelete(const std::string key);

                const int dbSize();
            };
        } // namespace db
    }     // namespace server
} // namespace raichu
