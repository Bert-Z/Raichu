#pragma once

#include "db.h"
#include <vector>

namespace raichu
{
    namespace server
    {
        class dbservice
        {
        private:
            static unsigned long nodenum;
            std::unordered_map<std::string, std::unique_ptr<db::db>> dbs;

            std::string createNode();
            std::string createNode(const std::string &name);
            void deleteNode(const std::string &name);

        public:
            void getAllNodeName(std::vector<std::string> &names);
            // PUT
            std::string Put(const std::string &name,const std::string &key,const std::string &value);
            // DELETE
            void Delete(const std::string &name,const std::string &key);
            // READ
            std::string Read(const std::string &name,const std::string &key);
        };
    } // namespace server
} // namespace raichu