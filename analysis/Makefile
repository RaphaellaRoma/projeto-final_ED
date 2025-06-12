# Compilação dos programas de análise
CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC = ../src
BIN = ../build

all: bst_analysis

bst_analysis: analysis_bst.cpp metrics.cpp $(SRC)/bst.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/analysis_bst analysis_bst.cpp metrics.cpp $(SRC)/bst.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp

clean:
	rm -f $(BIN)/analysis_bst
