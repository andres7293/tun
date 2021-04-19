CXX=g++
CXXFLAGS=-g -Wall -std=c++11

main.out:	main.cc IPv4.o
	${CXX} ${CXXFLAGS} $^ -o $@

IPv4.o:	IPv4.cc
	${CXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm -f *.o *.out
