CXX=g++ -std=gnu++0x
CFLAGS=-c -Wall 
LDFLAGS+=-lgsl

all: gaussexp

gaussexp: main.o gslwrapper.o gelements.o
	$(CXX) $(LDFLAGS) main.o gslwrapper.o gelements.o -o gaussexp
main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp
gslwrapper.o: src/gslwrapper.cpp
	    $(CXX) $(CFLAGS) src/gslwrapper.cpp 
gelements.o: src/gelements.cpp
	    $(CXX) $(CFLAGS) src/gelements.cpp 
clean:
	rm -rf *o gaussexp