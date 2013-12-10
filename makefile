CXX=g++
CFLAGS=-c -Wall 
LDFLAGS+=-lgsl

all: gaussexp

gaussexp: main.o gslwrapper.o
	$(CXX) $(LDFLAGS) main.o src/gslwrapper.o  -o gaussexp
main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp
gslwrapper.o: src/gslwrapper.cpp
	    $(CXX) $(CFLAGS) src/gslwrapper.cpp
clean:
	rm -rf *o gaussexp