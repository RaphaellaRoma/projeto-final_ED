# Diretórios
SRC = src
BUILD = build

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(SRC)

# Arquivos comuns
COMMON = $(SRC)/data.cpp $(SRC)/tree_utils.cpp

# Alvos principais
all: bst avl rbt test_bst test_avl test_rbt

bst:
	$(CXX) $(CXXFLAGS) -o $(BUILD)/bst $(COMMON) $(SRC)/bst.cpp $(SRC)/main_bst.cpp

avl:
	$(CXX) $(CXXFLAGS) -o $(BUILD)/avl $(COMMON) $(SRC)/avl.cpp $(SRC)/main_avl.cpp

rbt:
	$(CXX) $(CXXFLAGS) -o $(BUILD)/rbt $(COMMON) $(SRC)/rbt.cpp $(SRC)/main_rbt.cpp

# Alvos de teste
test_bst:
	$(CXX) $(CXXFLAGS) -o $(BUILD)/test_bst $(COMMON) $(SRC)/bst.cpp $(SRC)/test_bst.cpp

test_avl:
	$(CXX) $(CXXFLAGS) -o $(BUILD)/test_avl $(COMMON) $(SRC)/avl.cpp $(SRC)/test_avl.cpp

test_rbt:
	$(CXX) $(CXXFLAGS) -o $(BUILD)/test_rbt $(COMMON) $(SRC)/rbt.cpp $(SRC)/test_rbt.cpp

# Limpeza
clean:
	rm -f $(BUILD)/*
