CC = /usr/bin/clang++
CFLAGS = --std=c++11 -Wall -Wextra
LDFLAGS = -pthread
INCLUDE = -I/usr/include/boost

all: src/main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) src/main.cpp -o ssfi

clean:
	rm -rf ssfi
	rm -rf build/*
