LIB_NAME	:= libmscm
DYNAMIC_LIB := $(LIB_NAME).so
STATIC_LIB	:= $(LIB_NAME).a

DIR_INC := ./include
DIR_SRC := ./src
DIR_OBJ := ./obj
DIR_LIB := ./lib
DIR_BIN := ./bin
CC		:= gcc
GXX		:= g++
LD		:= ld
AR		:= ar
RANLIB	:= ranlib
ARFLAGS := -rc
DEFINES :=
INCLUDE := #-I/opt/ros/kinetic/include
LIBS	:= -L$(DIR_LIB) #-L/opt/ros/kinetic/lib
CXXFLAGS:= -g -Wall -O3 -fpic #-std=c++11
SHARE	:= -shared -fPIC -llcm -lstdc++
LDFLAGS :=  -llcm -lstdc++

SRC := $(wildcard ${DIR_SRC}/*.cpp)
OBJ := $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC}))
HDR := $(wildcard ${DIR_SRC}/*.h ${DIR_SRC}/*.hpp)

.PHONY : dir lib inc clean veryclean rebuild example

all : dir lib inc example

#lib : $(DYNAMIC_LIB) $(STATIC_LIB) inc
lib : $(DYNAMIC_LIB) inc

inc:
	@echo Copying headers 
	@for file in $(HDR); \
	do \
		echo copying $$file; \
		cp "$$file" $(DIR_INC); \
	done

dir :
	@mkdir -p obj
	@mkdir -p lib
	@mkdir -p bin

include example/Makefile.in

${DIR_OBJ}/%.o : ${DIR_SRC}/%.cpp
	@echo Compiling $< ...
	$(GXX) $(CXXFLAGS) -o $@ -c $< $(DEFINES) $(INCLUDE)

$(DYNAMIC_LIB) : $(OBJ)
	$(GXX) $(SHARE) -o $(DIR_LIB)/$(DYNAMIC_LIB) $(OBJ)

$(STATIC_LIB) : $(OBJ)
	$(AR) $(ARFLAGS) $(DIR_LIB)/$@ $^
	$(RANLIB) $(DIR_LIB)/$@

rebuild : veryclean all

clean :
	rm -rf $(DIR_OBJ)/*.o
	rm -rf $(DIR_BIN)/*

veryclean : clean
	rm -rf $(DIR_LIB)/*.so $(DIR_LIB)/*.a

