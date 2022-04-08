CC = clang++
CFLAGS = -Wall -g -O2 -std=c++11 -march=native -mfpmath=sse -flto -ftree-vectorize -fopenmp -mtune=generic 
NAME = main

$(NAME): src/*.cpp src/network/*.cpp
	$(CC) $(CFLAGS) src/*.cpp src/network/*.cpp -o $(NAME)
