#pragma once

#include "../server/utils/zk/zk_cpp.h"
#include <mutex>
#include <condition_variable>

namespace raichu
{
    namespace lock
    {
        // Simple CountDownLatch Implementation
        class CountDownLatch
        {
        private:
            std::mutex m_mutex;
            std::condition_variable m_cv;
            unsigned int m_count = 0;

        public:
            explicit CountDownLatch(const unsigned int count) : m_count(count) {}

            void await(void);
            void countDown(void);
            unsigned int getCount(void);
        };

        class ReadWriteLock
        {
        private:
            raichu::server::zk::zk_cpp zk_client;
            std::string lock_name;
            std::string read_lock;
            std::string write_lock;

            enum LockType
            {
                Read = 0,
                Write
            };

            inline bool matchLockType(const std::string &path, LockType locktype);

        public:
            explicit ReadWriteLock(const std::string &host_name, const std::string &lock_name) : lock_name(lock_name)
            {
                zk_client.connect(host_name);
                if (zk_client.exists_node(lock_name.c_str(), nullptr, true) != raichu::server::zk::z_ok)
                {
                    std::vector<raichu::server::zk::zoo_acl_t> acl;
                    acl.push_back(raichu::server::zk::zk_cpp::create_world_acl(raichu::server::zk::zoo_perm_all));
                    zk_client.create_persistent_node(lock_name.c_str(), "0", acl);
                }
            }

            void sortNode(std::vector<std::string> &vec);

            // get read lock
            void lockRead();

            // release read lock
            void unLockRead();

            // get write lock
            void lockWrite();

            // release write lock
            void unLockWrite();
        };
    } // namespace lock
} // namespace raichu