# (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

# compiler settings
CXX = g++
# CXX = clang++
CXXFLAGS = -ansi -pedantic -Wall -Wextra -Wconversion -pthread -std=c++23
LDFLAGS = -lm

all: a_helloworld.out a_helloworld_explained.out

a_helloworld.out: snippets/a_helloworld.cpp
	$(CXX) $(CXXFLAGS)  snippets/a_helloworld.cpp $(LDFLAGS) -o a_helloworld.out

a_helloworld_explained.out: snippets/a_helloworld_explained.cpp
	$(CXX) $(CXXFLAGS)  snippets/a_helloworld_explained.cpp $(LDFLAGS) -o a_helloworld_explained.out

clean:
	rm *.out
