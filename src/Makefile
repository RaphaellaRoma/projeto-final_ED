CXX = g++
CXXFLAGS = -Wall -O2

# Alvo padrão compila tudo
all: bst avl rbt

# Regras para gerar cada executável

bst: data.o bst.o main_bst.o
	$(CXX) $(CXXFLAGS) -o bst data.o bst.o main_bst.o

avl: data.o avl.o main_avl.o
	$(CXX) $(CXXFLAGS) -o avl data.o avl.o main_avl.o

rbt: data.o rbt.o main_rbt.o
	$(CXX) $(CXXFLAGS) -o rbt data.o rbt.o main_rbt.o

# Regras para compilar os objetos

data.o: data.cpp
	$(CXX) $(CXXFLAGS) -c data.cpp

bst.o: bst.cpp
	$(CXX) $(CXXFLAGS) -c bst.cpp

avl.o: avl.cpp
	$(CXX) $(CXXFLAGS) -c avl.cpp

rbt.o: rbt.cpp
	$(CXX) $(CXXFLAGS) -c rbt.cpp

main_bst.o: main_bst.cpp
	$(CXX) $(CXXFLAGS) -c main_bst.cpp

main_avl.o: main_avl.cpp
	$(CXX) $(CXXFLAGS) -c main_avl.cpp

main_rbt.o: main_rbt.cpp
	$(CXX) $(CXXFLAGS) -c main_rbt.cpp

# Limpeza
clean:
	rm -f *.o bst avl rbt
