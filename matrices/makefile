CC = g++
CFLAGS = -Wall -g --std=c++17 -fsanitize=undefined,address

main: main.o matrix.o 
	$(CC) $(CFLAGS) -o main main.o matrix.o

main.o: main.cpp matrix.h
	$(CC) $(CFLAGS) -c main.cpp

matrix.o: matrix.h 

clean:
	rm *.o main
