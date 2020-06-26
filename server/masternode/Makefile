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

PROTOS_PATH = ../../rpc-proto/

RPCSERVICE_PATH = ../utils/rpcservice/

vpath %.proto $(PROTOS_PATH)

all: master

master: $(PROTOS_PATH)rpc.pb.o $(PROTOS_PATH)rpc.grpc.pb.o $(RPCSERVICE_PATH)service.h master.o
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	rm -f *.o master
    
