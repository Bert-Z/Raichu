#include "lock.h"
#include <algorithm>

namespace raichu
{
    namespace lock
    {
        // Simple CountDownLatch Implementation
        void CountDownLatch::await(void)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_count > 0)
            {
                m_cv.wait(lock, [this]() { return m_count == 0; });
            }
        }

        void CountDownLatch::countDown(void)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_count > 0)
            {
                m_count--;
                m_cv.notify_all();
            }
        }

        unsigned int CountDownLatch::getCount(void)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            return m_count;
        }

        // sort via sequence
        void ReadWriteLock::sortNode(std::vector<std::string> &vec)
        {

            std::sort(vec.begin(), vec.end(), [](std::string &s1, std::string &s2) {
                return std::stoi(s1.substr(s1.find("-") + 1)) < std::stoi(s2.substr(s2.find("-") + 1));
            });
        }

        inline bool ReadWriteLock::matchLockType(const std::string &path, LockType locktype)
        {
            return path.substr(path.find("-") + 1)[0] == std::to_string(locktype)[0];
        }

        // get read lock
        void ReadWriteLock::lockRead()
        {
            std::unique_ptr<CountDownLatch> readlatch(new CountDownLatch(1));
            // create sequance ephemeral node
            std::string nodename_prefix = lock_name + "/" + std::to_string(LockType::Read) + "-";
            std::vector<raichu::server::zk::zoo_acl_t> acl;
            acl.push_back(raichu::server::zk::zk_cpp::create_world_acl(raichu::server::zk::zoo_perm_all));
            zk_client.create_sequance_ephemeral_node(nodename_prefix.c_str(), "0", acl, this->read_lock);

            // find the write_lock before this lock
            std::vector<std::string> all_locks;
            zk_client.get_children(lock_name.c_str(), all_locks, true);
            sortNode(all_locks);

            int size = all_locks.size();
            int tmp_index = 0;
            for (int i = size - 1; i >= 0; i--)
            {
                if (lock_name + "/" + all_locks[i] == this->read_lock)
                {
                    tmp_index = i;
                }
                else if (i < tmp_index && matchLockType(all_locks[i], LockType::Write))
                {
                    std::string write_node_path = lock_name + "/" + all_locks[i];
                    // child change events
                    auto child_change_events = [this, &readlatch, &write_node_path](const std::string &path, const std::vector<std::string> &children) {
                        if (this->zk_client.exists_node(write_node_path.c_str(), nullptr, true) == raichu::server::zk::z_ok)
                        {
                            readlatch->countDown();
                        }
                    };
                    zk_client.watch_children_event(lock_name.c_str(), child_change_events, &all_locks);

                    readlatch->await();

                    break;
                }
            }
        }

        // release read lock
        void ReadWriteLock::unLockRead()
        {
            if (this->read_lock != "")
            {
                zk_client.delete_node(this->read_lock.c_str(), -1);
                this->read_lock = "";
            }
        }

        // get write lock
        void ReadWriteLock::lockWrite()
        {
            std::unique_ptr<CountDownLatch> writelatch(new CountDownLatch(1));
            // create sequance ephemeral node
            std::string nodename_prefix = lock_name + "/" + std::to_string(LockType::Write) + "-";
            std::vector<raichu::server::zk::zoo_acl_t> acl;
            acl.push_back(raichu::server::zk::zk_cpp::create_world_acl(raichu::server::zk::zoo_perm_all));
            zk_client.create_sequance_ephemeral_node(nodename_prefix.c_str(), "0", acl, this->write_lock);

            // get all locks
            std::vector<std::string> all_locks;
            zk_client.get_children(lock_name.c_str(), all_locks, true);
            sortNode(all_locks);

            int size = all_locks.size();
            for (int i = size - 1; i >= 0; i--)
            {
                // find this writelock in the list
                if (this->write_lock == lock_name + "/" + all_locks[i])
                {
                    // there is still some locks before this writelock, then wait
                    if (i > 0)
                    {
                        auto child_change_events = [this, &writelatch](const std::string &path, const std::vector<std::string> &children) {
                            if (lock_name + "/" + children[0] == this->write_lock)
                            {
                                writelatch->countDown();
                            }
                        };

                        zk_client.watch_children_event(lock_name.c_str(), child_change_events, &all_locks);

                        writelatch->await();
                        break;
                    }
                }
            }
        }

        // release write lock
        void ReadWriteLock::unLockWrite()
        {
            if (this->write_lock != "")
            {
                zk_client.delete_node(this->write_lock.c_str(), -1);
                this->write_lock = "";
            }
        }
    } // namespace lock
} // namespace raichu