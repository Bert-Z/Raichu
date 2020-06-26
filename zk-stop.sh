#!/bin/bash

# run node1
cd /usr/local/zookeeper/zookeeper-3.4.13/bin
sudo ./zkServer.sh stop

# run node2
cd /usr/local/zookeeper/zookeeper-node2/bin
sudo ./zkServer.sh stop

# run node3
cd /usr/local/zookeeper/zookeeper-node3/bin
sudo ./zkServer.sh stop

