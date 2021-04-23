CCXX=g++
CXXFLAGS=-g -Wall -std=c++17
LIBS=-lgtest -lpthread
SOURCES=IP_test.cc
OBJECTS=$(SOURCES:.cc=.o)

all: test

test:	test.o
	make -C ../ IP.o
	make -C ../ Utils.o
	${CCXX} ${CXXFLAGS} $^ ../IP.o ../Utils.o -o $@ ${LIBS}

%.o:	%.cc
	${CCXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm -f *.o *.out IPv4_test
