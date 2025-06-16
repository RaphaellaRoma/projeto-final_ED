# Compilação dos programas de análise
CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC = ../src
BIN = ../build

all: bst_analysis avl_analysis rbt_analysis

bst_analysis: analysis_bst.cpp metrics.cpp $(SRC)/bst.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/analysis_bst analysis_bst.cpp metrics.cpp $(SRC)/bst.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp

avl_analysis: analysis_avl.cpp metrics.cpp $(SRC)/avl.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/analysis_avl analysis_avl.cpp metrics.cpp $(SRC)/avl.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp

rbt_analysis: analysis_rbt.cpp metrics.cpp $(SRC)/rbt.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/analysis_rbt analysis_rbt.cpp metrics.cpp $(SRC)/rbt.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp


clean:
	rm -f $(BIN)/analysis_bst $(BIN)/analysis_avl $(BIN)/analysis_rbt 
