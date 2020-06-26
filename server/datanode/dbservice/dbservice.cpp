#include "dbservice.h"

namespace raichu
{
    namespace server
    {
        unsigned long dbservice::nodenum = 0;

        std::string dbservice::createNode()
        {
            std::string name = "datanode" + std::to_string(nodenum);
            dbs[name] = std::unique_ptr<db::db>(new db::db(name));
            return name;
        }

        std::string dbservice::createNode(const std::string &name)
        {
            if (dbs.find(name) != dbs.end())
                return name + " has been created.";
            dbs[name] = std::unique_ptr<db::db>(new db::db(name));
            return name;
        }

        void dbservice::deleteNode(const std::string &name)
        {
            dbs.erase(name);
        }

        void dbservice::getAllNodeName(std::vector<std::string> &names)
        {
            names.clear();
            for (auto &node : dbs)
                names.emplace_back(node.first);
        }

        // PUT
        std::string dbservice::Put(const std::string &name, const std::string &key, const std::string &value)
        {
            if (dbs.find(name) == dbs.end())
                createNode(name);

            dbs[name]->dbPut(key, value);
            return key + ":" + value;
        }
        // DELETE
        void dbservice::Delete(const std::string &name, const std::string &key)
        {
            dbs[name]->dbDelete(key);
        }
        // READ
        std::string dbservice::Read(const std::string &name, const std::string &key)
        {
            if (dbs.find(name) == dbs.end())
                return "dbnode: " + name + " not found.";

            return dbs[name]->dbRead(key);
        }
    } // namespace server
} // namespace raichu