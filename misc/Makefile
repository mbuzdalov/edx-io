C=gcc
CXX=g++
DYFLAGS=-fPIC -c
CFLAGS=-O3 -Wall -Wpedantic
CXXFLAGS=-O3 -Wall -Wpedantic
LDFLAGS=-O3

ROOT_C=../src/c
ROOT_CPP=../src/c++

checkme: libedx.so
	@echo ""
	@echo "Checking whether libedx.so is sane"
	$(CXX) $(LDFLAGS) -I$(ROOT_C) -I$(ROOT_CPP) -o checkme checkme.cpp -L. -ledx
	echo "3 4" > input.txt
	LD_LIBRARY_PATH=. ./checkme
	rm input.txt checkme
	test `cat output.txt` -eq "7"
	rm output.txt
	@echo "libedx.so is sane"

libedx.so: edx-c.o edx-cpp.o
	$(CXX) $(LDFLAGS) -shared -o libedx.so edx-cpp.o edx-c.o

edx-c.o:
	$(C) $(CFLAGS) $(DYFLAGS) -I$(ROOT_C) -o edx-c.o $(ROOT_C)/edx-io.c

edx-cpp.o:
	$(CXX) $(CXXFLAGS) $(DYFLAGS) -I$(ROOT_C) -I$(ROOT_CPP) -o edx-cpp.o $(ROOT_CPP)/edx-io.cpp

clean:
	rm -f libedx.so edx-c.o edx-cpp.o checkme input.txt output.txt
