CC			= g++
#CFLAGS		= -fPIC -std=c++14 -c -Wall -Wextra -O2 -g
CFLAGS		= -fPIC -std=c++11 -c -Wall -Wextra -O2 -g
LDFLAGS		= -shared 
SOURCES		= $(shell echo *.cpp)
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.cpp=.o)
DEP_INC		= $(SOURCES:.cpp=.d)
TARGETSO	= libmongame.so
TARGETAR	= libmongame.a

all: $(SOURCES) $(TARGETSO) $(TARGETAR)

$(TARGETSO): $(OBJECTS) 
	@echo "----- Building shared lib: $@"
	$(CC) $(LDFLAGS) $^ -o $@

$(TARGETAR): $(OBJECTS) 
	@echo "----- Building static lib: $@"
	ar rcs $@ $^

%.d: %.cpp
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

-include $(DEP_INC)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGETSO) $(TARGETAR)
	rm -f $(DEP_INC)
