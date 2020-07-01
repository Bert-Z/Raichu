CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11

PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

OPT = -pipe -fno-ident 
LDFLAGS+= $(OPT) -g -O0 -Wall -pg -D_GNU_SOURCE -funroll-loops  -D_REENTRANT -lzookeeper_mt 

ZK_PATH = ../server/utils/zk/

INC += -I.  -I/usr/local/include/zookeeper
		 
LIB += -lrt -lm -lz 

all: locktest

locktest: $(ZK_PATH)zk_cpp.o lock.o locktest.o
	$(CXX) $^ $(LDFLAGS) -o $@ $(LIB) $(INC) 

clean:
	rm -f *.o locktest
    
