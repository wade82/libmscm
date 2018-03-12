CXX = g++
CFLAGS = 
CXXFLAGS = -O2 -g -Wall -fmessage-length=0
LDFLAGS = -llcm
DIR_INC := ../include
DIR_LIB := ../lib
INCLUDE := -I$(DIR_INC)
LIBS    := #-L$(DIR_LIB) -lmscm

SRCS = $(wildcard *.cpp)  
OBJS = $(patsubst %cpp, %o, $(SRCS))  #利用模式匹配生成.o文件 
TARGET = $(patsubst %.cpp, %.exe, $(SRCS))
STATIC_TARGET = $(patsubst %.cpp, s%.exe, $(SRCS))

all: $(TARGET) #$(STATIC_TARGET)

%.exe : %.o
	$(CXX) $(CFLAGS) -o $@ $< $(DIR_LIB)/libmscm.so $(LDFLAGS) $(LIBS)
s%.exe : %.o
	$(CXX) $(CFLAGS) -o $@ $< $(DIR_LIB)/libmscm.a $(LDFLAGS)
%.o : %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@ $(INCLUDE) $(LIBS)

.PHONY : clean

clean:
	rm -f $(OBJS) $(TARGET) $(STATIC_TARGET)
