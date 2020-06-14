# Raichu

## System Environment





## Zookeeper Install & Configuration

### 1. Zookeeper Install

```shell
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

```

### 2. Modify Env Path

```shell
vim /etc/profile
```

Add these two lines.

```
export ZK_HOME=/usr/local/zookeeper/apache-zookeeper
export PATH=$ZK_HOME/bin:$PATH
```

Then

```shell
source /etc/profile
```

### 3. Modify zoo.cfg

```shell
cd /usr/local/zookeeper/apache-zookeeper/conf
cp zoo_sample.cfg zoo.cfg
vim zoo.cfg
```

Make  `dataDir=/usr/local/zookeeper/data`

```shell
# The number of milliseconds of each tick
tickTime=2000
# The number of ticks that the initial
# synchronization phase can take
initLimit=10
# The number of ticks that can pass between
# sending a request and getting an acknowledgement
syncLimit=5
# the directory where the snapshot is stored.
# do not use /tmp for storage, /tmp here is just
# example sakes.


# 只需要修改此处为zookeeper数据存放位置
dataDir=/usr/local/zookeeper/data
# the port at which the clients will connect
clientPort=2181
# the maximum number of client connections.
# increase this if you need to handle more clients
#maxClientCnxns=60
#
# Be sure to read the maintenance section of the
# administrator guide before turning on autopurge.
#
# http://zookeeper.apache.org/doc/current/zookeeperAdmin.html#sc_maintenance
#
# The number of snapshots to retain in dataDir
#autopurge.snapRetainCount=3
# Purge task interval in hours
# Set to "0" to disable auto purge feature
#autopurge.purgeInterval=1             
```

### 4. Run

```shell
cd /usr/local/zookeeper/apache-zookeeper/bin

# run
./zkServer.sh start

ZooKeeper JMX enabled by default
Using config: /usr/local/zookeeper/apache-zookeeper/bin/../conf/zoo.cfg
Starting zookeeper ... STARTED

# show state
./zkServer.sh status 
ZooKeeper JMX enabled by default
Using config: /usr/local/zookeeper/apache-zookeeper/bin/../conf/zoo.cfg
Mode: standalone
```