#!/bin/sh

# install the running environment of zk
sudo apt-get install openjdk-8-jre

# download zk
wget https://archive.apache.org/dist/zookeeper/zookeeper-3.4.13/zookeeper-3.4.13.tar.gz

# unzip zk
tar -xvf zookeeper-3.4.13.tar.gz

# move the zk dir to the directed dir
sudo mv zookeeper-3.4.13 /usr/local/zookeeper/zookeeper-3.4.13

# create the soft link to zk dir
sudo ln -s /usr/local/zookeeper/zookeeper-3.4.13 /usr/local/zookeeper/apache-zookeeper
