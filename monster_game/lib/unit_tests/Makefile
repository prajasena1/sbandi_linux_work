CC			= g++
#CFLAGS		= -fPIC -std=c++14 -c -Wall -Wextra -O2 -g -L ../lib
CFLAGS		= -fPIC -std=c++11 -c -Wall -Wextra -O2 -g -L ../lib -L /usr/lib64/gtest
LDFLAGS		= -L../lib -L /usr/lib64/gtest -Bdynamic -lpthread -lgtest
SOURCES		= $(shell echo *.cpp)
INCLUDES	= -I../lib
OBJECTS		= $(SOURCES:.cpp=.o)
DEP_LIB		= ../libmongame.a
LIBS		= -Bstatic $(DEP_LIB)
TARGET		= mongame_utest

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) $(DEP_LIB)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

.PHONY: clean test
clean:
	rm -rf $(OBJECTS) $(TARGET) report.xml

test: all
	./$(TARGET) --gtest_output="xml:report.xml"


