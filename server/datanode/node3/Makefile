HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
ifeq ($(SYSTEM),Darwin)
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread\
           -lgrpc++_reflection\
           -ldl
else
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl
endif
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = ../../../rpc-proto/

RPCSERVICE_PATH = ../../utils/rpcservice/

DBSERVICE_PATH = ../dbservice/

OPT = -pipe -fno-ident 
LDFLAGS+= $(OPT) -g -O0 -Wall -pg -D_GNU_SOURCE -funroll-loops  -D_REENTRANT -lzookeeper_mt 

ZK_PATH = ../../utils/zk/

INC += -I.  -I/usr/local/include/zookeeper
		 
		
LIB += -lrt -lm -lz 

vpath %.proto $(PROTOS_PATH)

all: node3

node3: $(PROTOS_PATH)rpc.pb.o $(PROTOS_PATH)rpc.grpc.pb.o $(RPCSERVICE_PATH)service.h $(DBSERVICE_PATH)dbservice.o $(DBSERVICE_PATH)db.o $(ZK_PATH)zk_cpp.o node3.o
	$(CXX) $^ $(LDFLAGS) -o $@ $(LIB) $(INC) 

clean:
	rm -f *.o node3
    
