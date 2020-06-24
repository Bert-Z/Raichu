RED = \\e[1m\\e[31m
DARKRED = \\e[31m 
GREEN = \\e[1m\\e[32m
DARKGREEN = \\e[32m 
BLUE = \\e[1m\\e[34m
DARKBLUE = \\e[34m 
YELLOW = \\e[1m\\e[33m
DARKYELLOW = \\e[33m 
MAGENTA = \\e[1m\\e[35m
DARKMAGENTA = \\e[35m 
CYAN = \\e[1m\\e[36m
DARKCYAN = \\e[36m 
RESET = \\e[m
CRESET =  ;echo -ne \\e[m; test -s $@

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
	@echo -e Linking $(CYAN)$@$(RESET) ...$(RED)
	@$(CXX) -o $@ $^ $(CFLAGS) $(LIB) $(CRESET)
	md5sum $(TARGET)
	
%.o: %.cpp Makefile
	@echo -e Compling $(GREEN)$<$(RESET) ...$(RED)
	@$(CXX) $(CFLAGS) -c -pg -o $@ $< $(INC) $(CRESET) 	 
	
%.o: %.c Makefile
	@echo -e Compling $(GREEN)$<$(RESET) ...$(RED)
	@$(CC) $(CFLAGS) -c -pg -o $@ $< $(INC) $(CRESET) 	
	
clean:
	@echo  $(OBJ) $(DEL_D) ../bin/$(TARGET) $(TARGET)
	@rm -f $(OBJ) $(DEL_D) ../bin/$(TARGET) $(TARGET)




