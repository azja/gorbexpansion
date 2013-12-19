CXX=g++ -std=gnu++0x -O2 -g
CFLAGS=-c -Wall 
LDFLAGS+=-lgsl
DIR=src
headers = $(wildcard headers/*.h)
all: gaussexp

gaussexp: main.o gslwrapper.o gelements.o gminimizer.o
	$(CXX) $(LDFLAGS) main.o gslwrapper.o gelements.o gminimizer.o  -o gaussexp
main.o: main.cpp ${headers}
	$(CXX) $(CFLAGS) main.cpp
gslwrapper.o: $(DIR)/gslwrapper.cpp ${headers}
	    $(CXX) $(CFLAGS) $(DIR)/gslwrapper.cpp 
gelements.o: $(DIR)/gelements.cpp ${headers}
	    $(CXX) $(CFLAGS) $(DIR)/gelements.cpp 
gminimizer.o: $(DIR)/gminimizer.cpp ${headers}
	    $(CXX) $(CFLAGS) $(DIR)/gminimizer.cpp 
clean:
	rm -rf *.o gaussexp