CCXX=g++
CXXFLAGS=-g -Wall -std=c++17
LIBS=-lgtest -lpthread
SOURCES=IP_test.cc
OBJECTS=$(SOURCES:.cc=.o)

all: test

test:	test.o
	make -C ../src IP.o
	make -C ../src Utils.o
	${CCXX} ${CXXFLAGS} $^ ../src/IP.o ../src/Utils.o -o $@ ${LIBS}

%.o:	%.cc
	${CCXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm -f *.o *.out IP_test
