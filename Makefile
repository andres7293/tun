CXX=g++
CXXFLAGS=-g -Wall -std=c++17
SOURCES=main.cc IPv4.cc Utils.cc
OBJECTS=$(SOURCES:.cc=.o)

main.out:	$(OBJECTS)
	${CXX} ${CXXFLAGS} $^ -o $@

%.o:	%.cc
	${CXX} ${CXXFLAGS} -c $^ -o $@

buildtest:
	make -C ./test all

cleantest:
	make -C ./test clean

runtest:
	./test/test

clean:
	rm -f *.o *.out
