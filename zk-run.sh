#!/bin/bash

# run node1 2181
cd /usr/local/zookeeper/zookeeper-3.4.13/bin
sudo ./zkServer.sh start

# run node2 2182
cd /usr/local/zookeeper/zookeeper-node2/bin
sudo ./zkServer.sh start

# run node3 2183
cd /usr/local/zookeeper/zookeeper-node3/bin
sudo ./zkServer.sh start

# show state
cd /usr/local/zookeeper/zookeeper-3.4.13/bin
./zkServer.sh status 
cd /usr/local/zookeeper/zookeeper-node2/bin
./zkServer.sh status 
cd /usr/local/zookeeper/zookeeper-node3/bin
./zkServer.sh status 
