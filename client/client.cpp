/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include <grpcpp/grpcpp.h>

#include "../rpc-proto/rpc.grpc.pb.h"
#include "../lock/lock.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

// KV client rpc
using rpc::KV;
using rpc::KVRequest;
using rpc::KVResponse;

class Client
{
public:
  Client(const std::string &master_node,
         std::shared_ptr<Channel> master_channel,
         std::shared_ptr<Channel> node2_channel,
         std::shared_ptr<Channel> node3_channel)
      : master_stub_(KV::NewStub(master_channel)),
        node2_stub_(KV::NewStub(node2_channel)),
        node3_stub_(KV::NewStub(node3_channel))
  {
    lock.reset(new raichu::lock::ReadWriteLock(master_node, "/lock"));
  }

  std::string Where(const std::string &key, const std::string &value = "")
  {
    KVRequest request;
    request.set_key(key);
    request.set_value(value);

    KVResponse response;

    ClientContext context;
    Status status = master_stub_->Where(&context, request, &response);
    std::string msg = response.message();
    if (status.ok())
    {
      std::cout << msg << std::endl;
      return msg;
    }
    else
    {
      if (msg.size() != 0)
      {
        std::cout << msg << std::endl;
        return "not exist";
      }

      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string Read(const std::string &key)
  {
    lock->lockRead();
    std::string msg = Where(key);
    if (msg == "RPC failed" || msg == "not exist")
    {
      return "Read failed";
    }

    KVRequest request;
    request.set_key(key);

    KVResponse response;

    ClientContext context;

    Status status;
    if (msg == "localhost:50052")
      status = node2_stub_->Read(&context, request, &response);
    else if (msg == "localhost:50053")
      status = node3_stub_->Read(&context, request, &response);
    else
      return "Wrong Read msg";

    lock->unLockRead();

    if (status.ok())
      return response.message();
    else
    {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string Put(const std::string &key, const std::string &value)
  {
    lock->lockWrite();
    std::string msg = Where(key, value);
    if (msg == "RPC failed" || msg == "not exist")
    {
      return "Read failed";
    }

    KVRequest request;
    request.set_key(key);
    request.set_value(value);

    KVResponse response;

    ClientContext context;
    Status status;
    if (msg == "localhost:50052")
      status = node2_stub_->Put(&context, request, &response);
    else if (msg == "localhost:50053")
      status = node3_stub_->Put(&context, request, &response);
    else
      return "Wrong Put msg";

    lock->unLockWrite();

    if (status.ok())
      return response.message();
    else
    {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  std::string Delete(const std::string &key)
  {
    lock->lockWrite();
    std::string msg = Where(key);
    if (msg == "RPC failed" || msg == "not exist")
    {
      return "Read failed";
    }

    KVRequest request;
    request.set_key(key);

    KVResponse response;

    ClientContext context;
    Status status;
    if (msg == "localhost:50052")
      status = node2_stub_->Delete(&context, request, &response);
    else if (msg == "localhost:50053")
      status = node3_stub_->Delete(&context, request, &response);
    else
      return "Wrong Delete msg";

    lock->unLockWrite();
    if (status.ok())
      return response.message();
    else
    {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

private:
  std::unique_ptr<KV::Stub> master_stub_;
  std::unique_ptr<KV::Stub> node2_stub_;
  std::unique_ptr<KV::Stub> node3_stub_;
  std::unique_ptr<raichu::lock::ReadWriteLock> lock;
};

void clientRun(const std::string &master_node, const std::string &node2, const std::string &node3)
{
  // kv client
  Client client("localhost:2182", grpc::CreateChannel(master_node, grpc::InsecureChannelCredentials()),
                grpc::CreateChannel(
                    node2, grpc::InsecureChannelCredentials()),
                grpc::CreateChannel(
                    node3, grpc::InsecureChannelCredentials()));

  // client user guild
  std::cout << "This is a kv storage system." << std::endl
            << "Operations: " << std::endl
            << " Help option: Help" << std::endl
            << " Quit option: Quit" << std::endl
            << " Read option:  Read <Key>" << std::endl
            << " Put option:  Put <Key> <Value>" << std::endl
            << " Delete option:  Delete <Key>" << std::endl;

  // input
  std::string line;
  std::vector<std::string> vec;
  std::cout << ">";
  while (std::getline(std::cin, line))
  {
    std::istringstream input(line);
    vec.clear();
    std::string str;
    int count = 0;
    while (std::getline(input, str, ' '))
    {
      count++;
      if (count > 3)
      {
        std::cout << "Wrong input!" << std::endl;
        break;
      }
      vec.push_back(str);
    }

    if (vec.size() == 1)
    {
      if (vec[0] == "Help")
      {
        std::cout << "This is a kv storage system." << std::endl
                  << "Operations: " << std::endl
                  << " Help option: Help" << std::endl
                  << " Quit option: Quit" << std::endl
                  << " Read option:  Read <Key>" << std::endl
                  << " Put option:  Put <Key>:<Value>" << std::endl
                  << " Delete option:  Delete <Key>" << std::endl;
      }
      else if (vec[0] == "Quit")
      {
        std::cout << "Thanks for using!" << std::endl;
        break;
      }
      else
        std::cout << "Wrong input!" << std::endl;
    }
    else if (vec.size() == 2)
    {
      if (vec[0] == "Read")
        std::cout << "Client received: " << client.Read(vec[1]) << std::endl;
      else if (vec[0] == "Delete")
        std::cout << "Client received: " << client.Delete(vec[1]) << std::endl;
      else
        std::cout << "Wrong input!" << std::endl;
    }
    else if (vec.size() == 3)
    {
      if (vec[0] == "Put")
        std::cout << "Client received: " << client.Put(vec[1], vec[2]) << std::endl;
      else
        std::cout << "Wrong input!" << std::endl;
    }

    std::cout << ">";
  }
}

int main(int argc, char **argv)
{
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str;
  std::string arg_str("--target");
  if (argc > 1)
  {
    std::string arg_val = argv[1];
    size_t start_pos = arg_val.find(arg_str);
    if (start_pos != std::string::npos)
    {
      start_pos += arg_str.size();
      if (arg_val[start_pos] == '=')
      {
        target_str = arg_val.substr(start_pos + 1);
      }
      else
      {
        std::cout << "The only correct argument syntax is --target=" << std::endl;
        return 0;
      }
    }
    else
    {
      std::cout << "The only acceptable argument is --target=" << std::endl;
      return 0;
    }
  }
  else
  {
    target_str = "localhost:50051";
  }

  std::string node2 = "localhost:50052", node3 = "localhost:50053";

  clientRun(target_str, node2, node3);

  return 0;
}
