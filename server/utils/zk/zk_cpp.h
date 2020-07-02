#pragma once

/** use the lib zookeeper as static lib */
#ifndef USE_STATIC_LIB
#define USE_STATIC_LIB
#endif

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <mutex>
#include <memory>
#include <unordered_map>
#include <functional>

namespace raichu
{
    namespace server
    {
        namespace zk
        {
            /** error code */
            enum zoo_rc
            {
                z_ok = 0, /*!< Everything is OK */

                /** System and server-side errors.
                * This is never thrown by the server, it shouldn't be used other than
                * to indicate a range. Specifically error codes greater than this
                * value, but lesser than {@link #api_error}, are system errors. */
                z_system_error = -1,
                z_runtime_inconsistency = -2, /*!< A runtime inconsistency was found */
                z_data_inconsistency = -3,    /*!< A data inconsistency was found */
                z_connection_loss = -4,       /*!< Connection to the server has been lost */
                z_marshalling_error = -5,     /*!< Error while marshalling or unmarshalling data */
                z_unimplemented = -6,         /*!< Operation is unimplemented */
                z_operation_timeout = -7,     /*!< Operation timeout */
                z_bad_arguments = -8,         /*!< Invalid arguments */
                z_invliad_state = -9,         /*!< Invliad zhandle state */

                /** API errors.
                * This is never thrown by the server, it shouldn't be used other than
                * to indicate a range. Specifically error codes greater than this
                * value are API errors (while values less than this indicate a
                * {@link #system_error}).
                */
                z_api_error = -100,
                z_no_node = -101,                   /*!< Node does not exist */
                z_no_auth = -102,                   /*!< Not authenticated */
                z_bad_version = -103,               /*!< Version conflict */
                z_no_children_for_ephemeral = -108, /*!< Ephemeral nodes may not have children */
                z_node_exists = -110,               /*!< The node already exists */
                z_not_empty = -111,                 /*!< The node has children */
                z_session_expired = -112,           /*!< The session has been expired by the server */
                z_invalid_callback = -113,          /*!< Invalid callback specified */
                z_invalid_acl = -114,               /*!< Invalid ACL specified */
                z_auth_failed = -115,               /*!< Client authentication failed */
                z_closing = -116,                   /*!< ZooKeeper is closing */
                z_nothing = -117,                   /*!< (not error) no server responses to process */
                z_session_moved = -118              /*!<session moved to another server, so operation is ignored */
            };

            /** permissions(ACL Consts)*/
            enum zoo_perm
            {
                zoo_perm_read = 1 << 0,
                zoo_perm_write = 1 << 1,
                zoo_perm_create = 1 << 2,
                zoo_perm_delete = 1 << 3,
                zoo_perm_admin = 1 << 4,
                zoo_perm_all = 0x1f,
            };

            enum zoo_scheme
            {
                zoo_scheme_world = 0,
                zoo_scheme_auth = 1,
                zoo_scheme_digest = 2,
                zoo_scheme_ip = 3,
            };

            struct zoo_acl_t
            {
                std::string scheme; // one of { 'world', 'auth', 'digest', 'ip'}
                std::string id;     // the value type is different case the scheme
                int32_t perm;       // see {@link #zoo_perm}

                zoo_acl_t() : perm(0) {}
                zoo_acl_t(const char *_scheme, const char *_id, int32_t _perm)
                    : scheme(_scheme), id(_id), perm(_perm)
                {
                }
            };

            /** zoo_state 
             * These constants represent the states of a zookeeper connection. They are
             * possible parameters of the watcher callback.
             */
            enum z_state
            {
                zoo_state_expired_session = -112,
                zoo_state_auth_failed = -113,
                zoo_state_closed = 0,
                zoo_state_connecting = 1,
                zoo_state_associating = 2,
                zoo_state_connected = 3,
            };

            /** internal log lvl */
            enum zoo_log_lvl
            {
                zoo_log_lvl_error = 1,
                zoo_log_lvl_warn = 2,
                zoo_log_lvl_info = 3,
                zoo_log_lvl_debug = 4,
            };

            /** zoo node info */
            struct zoo_state_t
            {
                int64_t ctime;          // node create time
                int64_t mtime;          // node last modify time
                int32_t version;        // node version
                int32_t children_count; // the number of children of the node
            };

            namespace utils
            {

                class noncopyable
                {
                protected:
                    noncopyable() {}
                    ~noncopyable() {}

                private:
                    noncopyable(const noncopyable &);
                    noncopyable &operator=(const noncopyable &);
                };
            } // namespace utils

            class zk_cpp : public utils::noncopyable
            {
            public:
                /** callbacks */
                /** watch events */

                /** the  path data change event call back */
                typedef std::function<void(const std::string &path, const std::string &new_value)> data_change_event_handler_t;
                typedef std::shared_ptr<data_change_event_handler_t> data_event_handler_ptr;

                typedef std::function<void(const std::string &path, const std::vector<std::string> &new_children)> child_event_handler_t;
                typedef std::shared_ptr<child_event_handler_t> child_event_handler_ptr;

            protected:
                typedef std::unordered_map<std::string, data_event_handler_ptr> data_event_map_type;
                typedef std::unordered_map<std::string, child_event_handler_ptr> child_event_map_type;

            protected:
                void *m_zh;        // zhandle_t
                std::string m_url; // zookeeper server urls

                std::mutex m_mtx;
                data_event_map_type m_data_event_map;
                child_event_map_type m_child_event_map;

            public:
                zk_cpp();
                ~zk_cpp();

            public:

                static const char *error_string(int32_t rc);

                static const char *state_to_string(int32_t state);

                static void set_log_lvl(zoo_log_lvl lvl);

                static void set_log_stream(FILE *file);

                static zoo_acl_t create_world_acl(int32_t perms);

                static zoo_acl_t create_auth_acl(int32_t perms);

                static zoo_acl_t create_digest_acl(int32_t perms, const std::string &user, const std::string &passwd);

                static zoo_acl_t create_ip_acl(int32_t perms, const std::string &ip_info);

            public:

                zoo_rc connect(const std::string &url);


                int32_t get_recv_time_out();

                z_state get_state();

                bool unrecoverable();

            public:
                /** events */

                /** event sesion connected */
                void on_session_connected();

                /** event session expired */
                void on_session_expired();

                /** event node created */
                void on_path_created(const char *path);

                /** event node delete */
                void on_path_delete(const char *path);

                /** event path data change */
                void on_path_data_change(const char *path);

                /** event path child change */
                void on_path_child_change(const char *path);

            protected:
                zoo_rc create_node(const char *path, const std::string &value, const std::vector<zoo_acl_t> &acl, int32_t create_flags, char *path_buffer, int32_t path_buffer_len);

            public:
                zoo_rc create_persistent_node(const char *path, const std::string &value, const std::vector<zoo_acl_t> &acl);

                zoo_rc create_sequence_node(const char *path, const std::string &value, const std::vector<zoo_acl_t> &acl, std::string &returned_path_name);

                zoo_rc create_sequance_ephemeral_node(const char *path, const std::string &value, const std::vector<zoo_acl_t> &acl, std::string &returned_path_name);

                zoo_rc delete_node(const char *path, int32_t version);

                zoo_rc exists_node(const char *path, zoo_state_t *info, bool watch);

                zoo_rc get_node(const char *path, std::string &out_value, zoo_state_t *info, bool watch);

                zoo_rc set_node(const char *path, const std::string &value, int32_t version);

                zoo_rc get_children(const char *path, std::vector<std::string> &children, bool watch);

                zoo_rc set_acl(const char *path, const std::vector<zoo_acl_t> &acl, int32_t version);

                zoo_rc get_acl(const char *path, std::vector<zoo_acl_t> &acl);

                zoo_rc add_auth(const std::string &user_name, const std::string &user_passwd);

                zoo_rc watch_data_change(const char *path, const data_change_event_handler_t &handler, std::string *value);

                zoo_rc watch_children_event(const char *path, const child_event_handler_t &handler, std::vector<std::string> *out_children);

            public:
                /*  asynchronous apis */

            protected:
                void close();
                void reconnect();
                void add_data_event_handler(const std::string &path, data_event_handler_ptr handler);
                void add_child_event_handler(const std::string &path, child_event_handler_ptr handler);
                data_event_handler_ptr get_data_event_handler(const std::string &path);
                child_event_handler_ptr get_child_event_handler(const std::string &path);
            };
        } // namespace zk

    } // namespace server

} // namespace raichu
