CC  = gcc
CXX = g++

OPT = -pipe -fno-ident 
#-z defs -e version

CFLAGS += $(OPT) -g -O0 -Wall -pg -D_GNU_SOURCE -funroll-loops -MMD -D_REENTRANT -std=c++11 -lzookeeper_mt 

ifeq ($(MEMCHECK),1)
CFLAGS += -DMEMCHECK
endif

#####The Debug option#####
DEBUG = -D__TEST__
CFLAGS += -fpermissive $(DEBUG)
SUBDIR=$(shell find ../ -maxdepth 1 -type d )

INC += -I.  -I/usr/local/include/zookeeper
		 
		
LIB += -lrt -lm -lz 

TARGET = test
  
SRC_FILES = $(wildcard *.cpp)   

SRC_C_FILES = $(wildcard *.c)   
						
OBJ =   $(SRC_FILES:.cpp=.o)  $(SRC_C_FILES:.c=.o)\
		
DEL_D = $(wildcard *.d)	 \
 
all:$(TARGET)

$(TARGET):$(OBJ)
	@$(CXX) -o $@ $^ $(CFLAGS) $(LIB) 
	
%.o: %.cpp Makefile
	@$(CXX) $(CFLAGS) -c -pg -o $@ $< $(INC) 
	
%.o: %.c Makefile
	@$(CC) $(CFLAGS) -c -pg -o $@ $< $(INC) 	
	
clean:
	@echo  $(OBJ) $(DEL_D) ../bin/$(TARGET) $(TARGET)
	@rm -f $(OBJ) $(DEL_D) ../bin/$(TARGET) $(TARGET)




