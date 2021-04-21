CCXX=g++
CXXFLAGS=-g -Wall -std=c++17
LIBS=-lgtest -lpthread

all: IPv4_test

IPv4_test:	IPv4_test.o
	make -C ../ IPv4.o
	${CCXX} ${CXXFLAGS} $^ ../IPv4.o -o $@ ${LIBS}

IPv4_test.o:	IPv4_test.cc
	${CCXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm -f *.o *.out IPv4_test
