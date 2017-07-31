CC			= g++
#CFLAGS		= -fPIC -std=c++14 -c -Wall -Wextra -O2 -g -L .. -L /usr/lib64/gtest
CFLAGS		= -fPIC -std=c++11 -c -Wall -Wextra -O2 -g -L .. -L /usr/lib64/gtest
LDFLAGS		= -L../lib -L /usr/lib64/gtest -Bdynamic -lpthread -lgtest
SOURCES		= $(shell echo *.cpp)
INCLUDES	= -I..
OBJECTS		= $(SOURCES:.cpp=.o)
DEP_INC		= $(SOURCES:.cpp=.d)
DEP_LIB		= ../libmongame.a
LIBS		= -Bstatic $(DEP_LIB)
TARGET		= mongame_utest

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) $(DEP_LIB)
	@echo "----- Building unit test executable $@"
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

%.d: %.cpp
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

-include $(DEP_INC)

.PHONY: clean test
clean:
	rm -f $(OBJECTS) $(TARGET) report.xml
	rm -f $(DEP_INC)

test: all
	./$(TARGET) --gtest_output="xml:report.xml"

