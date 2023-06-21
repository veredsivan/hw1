XX = g++
CXXLINK = $(CXX)
CXXFLAGS = -g -Wall -std=c++11
LDLIBS = -L/path/to/libraries/ -lfirewall -linput
OBJS = ip.o port.o string.o 
SOFILES = libfirewall.so libinput.so
CPPFILES = main.cpp string.cpp ip.cpp port.cpp
EXEC = firewall.exe
OFLAGS = $(CXX) $(CXXFLAGS) -fpic -c
RM = rm -rf


all: $(EXEC)

firewall.exe: main.o $(SOFILES)
	$(CXXLINK) -g main.o -L. $(LDLIBS) -o $(EXEC)

libfirewall.so: $(OBJS)
	$(CXX) -shared $(OBJS) -o libfirewall.so
	
main.o: $(CPPFILES)
	$(OFLAGS) main.cpp
	
string.o: string.cpp string.h
	$(OFLAGS) string.cpp

port.o: port.cpp port.h string.h
	$(OFLAGS) port.cpp

ip.o: ip.cpp ip.h string.h
	$(OFLAGS) ip.cpp

clean:
	$(RM) *.o libfirewall.so $(EXEC)