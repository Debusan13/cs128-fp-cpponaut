CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -fstandalone-debug -Wall -Wextra -pedantic 

exec: bin/exec
tests: bin/tests

bin/exec: ./src/*.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

bin/tests: ./tests/tests.cc obj/catch.o $(filter-out, ./src/*.cc)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/* obj/*
