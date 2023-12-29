INCLUDES=-IMovies
CXXFLAGS=-std=c++20 -g -fstandalone-debug -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

clean:
	rm -f bin/*

exec: movies.cpp main.cpp
	$(CXX) $(CXXFLAGS) $^ -o exec

.PHONY: clean exec