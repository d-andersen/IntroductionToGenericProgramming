CXX=g++-11
CPPFLAGS=-I../src
CXXFLAGS=-std=c++20 -g -Wall -Wextra $(SANFLAGS)
LDFLAGS=$(SANFLAGS)
SANFLAGS=-fsanitize=undefined -fsanitize=address -fsanitize=leak

EXE=ListTest TreeTest
OBJ=ListTest.o TreeTest.o

.PHONY: all
all: $(EXE)

ListTest: ListTest.o #../src/List.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

TreeTest: TreeTest.o #../src/Tree.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(EXE) *.o ../src/*.o