CC = g++
CFLAGS = -std=c++11
src = $(wildcard ./src/*.cpp)
src_tests := $(filter-out ./src/main.cpp, $(src)) \
             $(wildcard ./tests/*.cpp)

main: $(src)
	$(CC) $(CFLAGS) $(src) -o ./bin/main

main_tests: $(src_tests)
	$(CC) $(CFLAGS) $(src_tests) -o ./bin/main_tests

