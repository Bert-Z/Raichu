#pragma once

#include "db.h"
#include <vector>
#include <thread>

namespace raichu
{
    namespace server
    {
        class dbservice
        {
        private:
            unsigned long backup_num;
            std::vector<std::unique_ptr<db::db>> backups;

            std::string createNode(int i);

            // PUT
            std::string Put(const std::string &key, const std::string &value);
            std::string tPut(int i, const std::string &key, const std::string &value);
            // DELETE
            void Delete(const std::string &key);
            void tDelete(int i, const std::string &key);
            // READ
            // set the first one as the primary node
            std::string Read(const std::string &key);
            std::string tRead(int i, const std::string &key);

        public:
            enum Op
            {
                READ = 0,
                PUT,
                DELETE
            };

            explicit dbservice(const int backup_num) : backup_num(backup_num),backups(backup_num)
            {
                std::thread threads[backup_num];
                for (int i = 0; i < backup_num; i++)
                {
                    threads[i] = std::thread(&dbservice::createNode, this, i);
                }
                for (int i = 0; i < backup_num; i++)
                    threads[i].join();
            }

            int getBackupSize();
            // 2PC protocol
            // check backups status
            bool commitRequest();
            // commit transactions
            std::string commitTransactions(Op op, const std::string &key, const std::string &value = "");
        };
    } // namespace server
} // namespace raichu