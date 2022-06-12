CC = g++
CFLAGS = -std=c++17 -Wall -g -fsanitize=undefined,address


all: bst avl

compile_test: clean binary_search_tree.h avl_tree.h compile_test.cpp
	$(CC) $(CFLAGS) compile_test.cpp

bst: clean binary_search_tree.h binary_search_tree_tests.cpp
	$(CC) $(CFLAGS) --coverage binary_search_tree_tests.cpp && ./a.out && gcov -mr binary_search_tree_tests.cpp

avl: clean avl_tree.h avl_tree_tests.cpp
	$(CC) $(CFLAGS) --coverage avl_tree_tests.cpp && ./a.out && gcov -mr avl_tree_tests.cpp

build_a_tree: clean binary_search_tree.h avl_tree.h build_a_tree.cpp
	$(CC) $(CFLAGS) build_a_tree.cpp && ./a.out

clean:
	rm -f *.gcov *.gcda *.gcno a.out

