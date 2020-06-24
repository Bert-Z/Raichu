#!/bin/bash

cd /usr/local/zookeeper/apache-zookeeper/bin

# run
sudo ./zkServer.sh start

# show state
./zkServer.sh status 
