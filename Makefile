CC = g++
CFLAGS = -Wall -g -O2 -std=c++11 -march=native
NAME = main

$(NAME): *.cpp
	$(CC) $(CFLAGS) *.cpp -o $(NAME)

run: $(NAME)
	./$(NAME)