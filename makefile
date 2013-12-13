CXX=g++ -std=gnu++0x
CFLAGS=-c -Wall 
LDFLAGS+=-lgsl
DIR=src
all: gaussexp

gaussexp: main.o gslwrapper.o gelements.o 
	$(CXX) $(LDFLAGS) main.o gslwrapper.o gelements.o  -o gaussexp
main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp
gslwrapper.o: $(DIR)/gslwrapper.cpp
	    $(CXX) $(CFLAGS) $(DIR)/gslwrapper.cpp 
gelements.o: $(DIR)/gelements.cpp
	    $(CXX) $(CFLAGS) $(DIR)/gelements.cpp 
clean:
	rm -rf *.o gaussexp