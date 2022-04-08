CC = g++
CFLAGS = -Wall -g -O2 -std=c++11 -march=native
NAME = main

$(NAME): src/*.cpp src/network/*.cpp
	$(CC) $(CFLAGS) src/*.cpp src/network/*.cpp -o $(NAME)
