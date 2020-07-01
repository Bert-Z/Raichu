#include "dbservice.h"

namespace raichu
{
    namespace server
    {
        std::string dbservice::createNode(int i)
        {
            std::string backup_name = "backup-" + std::to_string(i);
            backups[i] = std::unique_ptr<db::db>(new db::db(backup_name));
            return backup_name;
        }

        int dbservice::getBackupSize()
        {
            return backup_num;
        }

        // PUT
        std::string dbservice::Put(const std::string &key, const std::string &value)
        {
            std::thread threads[backup_num];
            for (int i = 0; i < backup_num; i++)
            {
                threads[i] = std::thread(&dbservice::tPut, this, i, key, value);
            }
            for (int i = 0; i < backup_num; i++)
                threads[i].join();

            return key + ":" + value;
        }
        std::string dbservice::tPut(int i, const std::string &key, const std::string &value)
        {
            backups[i]->dbPut(key, value);
            return key + ":" + value;
        }
        // DELETE
        void dbservice::Delete(const std::string &key)
        {
            std::thread threads[backup_num];
            for (int i = 0; i < backup_num; i++)
            {
                threads[i] = std::thread(&dbservice::tDelete, this, i, key);
            }
            for (int i = 0; i < backup_num; i++)
                threads[i].join();
        }
        void dbservice::tDelete(int i, const std::string &key)
        {
            backups[i]->dbDelete(key);
        }
        // READ
        std::string dbservice::Read(const std::string &key)
        {
            // set the first one as the primary node
            return backups[0]->dbRead(key);
        }
        std::string dbservice::tRead(int i, const std::string &key)
        {
            return backups[i]->dbRead(key);
        }

        // 2PC protocol
        // check backups status
        bool dbservice::commitRequest()
        {
            if (backups.size() == backup_num)
                return true;
            return false;
        }
        // commit transactions
        std::string dbservice::commitTransactions(Op op, const std::string &key, const std::string &value)
        {
            switch (op)
            {
            case Op::READ:
                return Read(key);
            case Op::PUT:
                return Put(key, value);
            case Op::DELETE:
                Delete(key);
                return "Delete " + key;
            default:
                return "Wrong Op";
            }
        }
    } // namespace server
} // namespace raichu