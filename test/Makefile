CCXX=g++
CXXFLAGS=-g -Wall -std=c++17
LIBS=-lgtest -lpthread
SOURCES=IP_test.cc
OBJECTS=$(SOURCES:.cc=.o)

all: test

test:	test.o
	make -C ../src IP.o
	make -C ../src ICMP.o
	make -C ../src NetDev.o
	make -C ../src TunIf.o
	make -C ../src Utils.o
	make -C ../src NetBuf.o
	${CCXX} ${CXXFLAGS} $^ ../src/IP.o ../src/ICMP.o ../src/TunIf.o ../src/NetDev.o ../src/Utils.o ../src/NetBuf.o -o $@ ${LIBS}

%.o:	%.cc
	${CCXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm -f *.o *.out test
