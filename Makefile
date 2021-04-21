CXX=g++
CXXFLAGS=-g -Wall -std=c++17

main.out:	main.cc IPv4.o
	${CXX} ${CXXFLAGS} $^ -o $@

IPv4.o:	IPv4.cc
	${CXX} ${CXXFLAGS} -c $^ -o $@

buildtest:
	make -C ./test all

cleantest:
	make -C ./test clean

runtest:
	./test/IPv4_test

clean:
	rm -f *.o *.out
