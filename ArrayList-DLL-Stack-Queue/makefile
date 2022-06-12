CC = g++
CFLAGS = -std=c++17 -Wall -g -fsanitize=undefined,address

all: array_list linked_list stack queue

compile_test: clean array_list.h doubly_linked_list.h stack.h queue.h compile_test.cpp
	$(CC) $(CFLAGS) compile_test.cpp

array_list: clean array_list.h array_list_tests.cpp
	$(CC) $(CFLAGS) --coverage array_list_tests.cpp && ./a.out && gcov -mr array_list_tests.cpp

linked_list: clean doubly_linked_list.h doubly_linked_list_tests.cpp
	$(CC) $(CFLAGS) --coverage doubly_linked_list_tests.cpp && ./a.out && gcov -mr doubly_linked_list_tests.cpp

stack: clean stack.h stack_tests.cpp
	$(CC) $(CFLAGS) --coverage stack_tests.cpp && ./a.out && gcov -mr stack_tests.cpp

queue: clean queue.h queue_tests.cpp
	$(CC) $(CFLAGS) --coverage queue_tests.cpp && ./a.out && gcov -mr queue_tests.cpp

clean:
	rm -f *.gcov *.gcda *.gcno a.out
