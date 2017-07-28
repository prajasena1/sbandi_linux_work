CC			= g++
#CFLAGS		= -fPIC -std=c++14 -c -Wall -Wextra -O2 -g -L ../lib
CFLAGS		= -fPIC -std=c++11 -c -Wall -Wextra -O2 -g -L ../lib
LDFLAGS		= -L../lib -Bdynamic -lpthread
SOURCES		= main.cpp
INCLUDES	= -I../lib
OBJECTS		= $(SOURCES:.cpp=.o)
DEP_LIB		= ../lib/libmongame.a
LIBS		= -Bstatic $(DEP_LIB)
TARGET		= mongame

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS) $(DEP_LIB)
	@echo "----- Building $@"
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGET)
