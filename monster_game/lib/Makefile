CC			= g++
#CFLAGS		= -fPIC -std=c++14 -c -Wall -Wextra -O2 -g
CFLAGS		= -fPIC -std=c++11 -c -Wall -Wextra -O2 -g
LDFLAGS		= -shared 
SOURCES		= $(shell echo *.cpp)
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.cpp=.o)
TARGETSO	= libmongame.so
TARGETAR	= libmongame.a

all: $(SOURCES) $(TARGETSO) $(TARGETAR)

$(TARGETSO): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(TARGETAR): $(OBJECTS) 
	ar rcs $(TARGETAR) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGETSO) $(TARGETAR)
