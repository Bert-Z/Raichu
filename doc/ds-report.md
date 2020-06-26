# Raichu

## System Environment

- Ubuntu18.04
- Zookeeper-3.4.13

## Zookeeper Cluster Install & Configuration

### 1. Zookeeper Cluster Install

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

# add two more nodes
cp -rf /usr/local/zookeeper/zookeeper-3.4.13   /usr/local/zookeeper/zookeeper-node2
cp -rf /usr/local/zookeeper/zookeeper-3.4.13   /usr/local/zookeeper/zookeeper-node3
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

Node1

```shell
#zookeeper时间单元，单位为毫秒
tickTime=2000
#集群中的follower服务器(F)与leader服务器(L)之间 初始连接 时能容忍的最多心跳数（tickTime的数量）。
initLimit=10
# 集群中的follower服务器(F)与leader服务器(L)之间 请求和应答 之间能容忍的最多心跳数（tickTime的数量）。
syncLimit=5
# data数据目录
dataDir=/usr/local/zookeeper/zookeeper-3.4.13/data
# 客户端连接端口
clientPort=2181
# 客户端最大连接数
#maxClientCnxns=60
# 需要保留的快照数目
#autopurge.snapRetainCount=3
# 是否开启自动清理事务日志和快照功能 0 不开启，1表示开启
#autopurge.purgeInterval=1
#集群配置 
server.1=127.0.0.1:2888:3888
server.2=127.0.0.1:2889:3889
server.3=127.0.0.1:2890:3890
```

Node2

```shell
#zookeeper时间单元，单位为毫秒
tickTime=2000
#集群中的follower服务器(F)与leader服务器(L)之间 初始连接 时能容忍的最多心跳数（tickTime的数量）。
initLimit=10
# 集群中的follower服务器(F)与leader服务器(L)之间 请求和应答 之间能容忍的最多心跳数（tickTime的数量）。
syncLimit=5
# data数据目录
dataDir=/usr/local/zookeeper/zookeeper-node2/data
# 客户端连接端口
clientPort=2182
# 客户端最大连接数
#maxClientCnxns=60
# 需要保留的快照数目
#autopurge.snapRetainCount=3
# 是否开启自动清理事务日志和快照功能 0 不开启，1表示开启
#autopurge.purgeInterval=1
#集群配置 
server.1=127.0.0.1:2888:3888
server.2=127.0.0.1:2889:3889
server.3=127.0.0.1:2890:3890
```

Node3

```shell
#zookeeper时间单元，单位为毫秒
tickTime=2000
#集群中的follower服务器(F)与leader服务器(L)之间 初始连接 时能容忍的最多心跳数（tickTime的数量）。
initLimit=10
# 集群中的follower服务器(F)与leader服务器(L)之间 请求和应答 之间能容忍的最多心跳数（tickTime的数量）。
syncLimit=5
# data数据目录
dataDir=//usr/local/zookeeper/zookeeper-node3/data
# 客户端连接端口
clientPort=2183
# 客户端最大连接数
#maxClientCnxns=60
# 需要保留的快照数目
#autopurge.snapRetainCount=3
# 是否开启自动清理事务日志和快照功能 0 不开启，1表示开启
#autopurge.purgeInterval=1
#集群配置 
server.1=127.0.0.1:2888:3888
server.2=127.0.0.1:2889:3889
server.3=127.0.0.1:2890:3890
```



### 4. ZK-run.sh

```shell
#!/bin/bash

# run node1
cd /usr/local/zookeeper/zookeeper-3.4.13/bin
sudo ./zkServer.sh start

# run node2
cd /usr/local/zookeeper/zookeeper-node2/bin
sudo ./zkServer.sh start

# run node3
cd /usr/local/zookeeper/zookeeper-node3/bin
sudo ./zkServer.sh start

# show state
cd /usr/local/zookeeper/zookeeper-3.4.13/bin
./zkServer.sh status 
cd /usr/local/zookeeper/zookeeper-node2/bin
./zkServer.sh status 
cd /usr/local/zookeeper/zookeeper-node3/bin
./zkServer.sh status 
```

### 5. C API Install

```shell
cd /usr/local/zookeeper/apache-zookeeper/src/c
make CFLAGS=-Wno-error=format-overflow 
sudo make install
sudo ldconfig
```

