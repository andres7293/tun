CXX=g++
CXXFLAGS=-g -Wall -std=c++17
SOURCES=main.cc IPv4.cc Utils.cc

main.out:	main.cc IPv4.o Utils.o
	${CXX} ${CXXFLAGS} $^ -o $@

IPv4.o:	IPv4.cc
	${CXX} ${CXXFLAGS} -c $^ -o $@

Utils.o:	Utils.cc
	${CXX} ${CXXFLAGS} -c $^ -o $@

buildtest:
	make -C ./test all

cleantest:
	make -C ./test clean

runtest:
	./test/IPv4_test

clean:
	rm -f *.o *.out
