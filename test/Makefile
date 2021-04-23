CCXX=g++
CXXFLAGS=-g -Wall -std=c++17
LIBS=-lgtest -lpthread
SOURCES=IPv4_test.cc
OBJECTS=$(SOURCES:.cc=.o)

all: test

test:	test.o
	make -C ../ IPv4.o
	make -C ../ Utils.o
	${CCXX} ${CXXFLAGS} $^ ../IPv4.o ../Utils.o -o $@ ${LIBS}

%.o:	%.cc
	${CCXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm -f *.o *.out IPv4_test
