# (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev
#
# make     						-> compiles all cpp in $SRC to $OBJ
# make all 						-> same
# make out/a_console_io.out		-> compiles only a_console_io
# make clear					-> removes files from out

# compiler settings
CXX := g++
# CXX := clang++
CXXFLAGS := -ansi -pedantic -Wall -Wextra -Wconversion -pthread -std=c++2a
LDFLAGS := -lm

SRC := ./snippets ./solutions
OBJ := ./out

# collect  files
CXXEXAMPLES = $(shell find $(SRC) -name '*.cpp' -print -type f)
CXXTARGETS = $(foreach file, $(CXXEXAMPLES), $(OBJ)/$(notdir $(file:.cpp=.out)))

# search path
vpath %.cpp $(SRC)
vpath %.out $(OBJ)

# build them all
all: $(CXXTARGETS)

# create 'out' if not exists
$(OBJ):
	mkdir -p $(OBJ)

# general rule with order-only prerequisite
$(OBJ)/%.out: %.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS)  $< $(LDFLAGS) -o $(OBJ)/$(@F)

clean:
	rm $(OBJ)/*.out
