# Compilação dos programas de análise do indice da BST, AVL e RBT
CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC = ../src
BIN = ../build

all: bst_analysis avl_analysis rbt_analysis general_analysis

bst_analysis: analysis_bst.cpp metrics.cpp $(SRC)/bst.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/analysis_bst analysis_bst.cpp metrics.cpp $(SRC)/bst.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp

avl_analysis: analysis_avl.cpp metrics.cpp $(SRC)/avl.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/analysis_avl analysis_avl.cpp metrics.cpp $(SRC)/avl.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp

rbt_analysis: analysis_rbt.cpp metrics.cpp $(SRC)/rbt.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/analysis_rbt analysis_rbt.cpp metrics.cpp $(SRC)/rbt.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp

general_analysis: analysis_general.cpp metrics.cpp $(SRC)/bst.cpp $(SRC)/avl.cpp $(SRC)/rbt.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)/analysis_general analysis_general.cpp metrics.cpp $(SRC)/bst.cpp $(SRC)/avl.cpp $(SRC)/rbt.cpp $(SRC)/tree_utils.cpp $(SRC)/data.cpp

clean:
	rm -f $(BIN)/analysis_bst $(BIN)/analysis_avl $(BIN)/analysis_rbt $(BIN)/analysis_general

.PHONY: all clean

