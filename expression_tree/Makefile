CXX := g++

INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
EXE := expr_tree

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS := --std=c++20 -I$(INC_DIR)

# .PHONY means these rules get executed even if
# files of those names exits.
.PHONY: all clean 

all: $(EXE)

$(EXE): $(OBJ) main.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -r obj
	rm $(EXE)
