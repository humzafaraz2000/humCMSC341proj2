CXX = g++
CXXFLAGS = -Wall

proj2: mytest.o
	$(CXX) $(CXXFLAGS) mytest.o -o proj2

mytest.o: rmqlist.h mytest.cpp
	$(CXX) $(CXXFLAGS) -c mytest.cpp

run:
	./proj2

val:
	valgrind ./proj2

