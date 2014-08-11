CC = /usr/bin/clang++
CFLAGS = --std=c++11 -Wall -Wextra
LDFLAGS = -pthread -lboost_system -lboost_filesystem -lboost_program_options -lboost_thread -lboost_log
INCLUDE = -I/usr/include/boost
DFLAGS = -DBOOST_LOG_DYN_LINK

all: src/main.cpp worker.o file_locator.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(DFLAGS) src/main.cpp build/worker.o build/file_locator.o -o ssfi

worker.o: src/worker.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(DFLAGS) -c src/worker.cpp -o build/worker.o

file_locator.o: src/file_locator.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(DFLAGS) -c src/file_locator.cpp -o build/file_locator.o

clean:
	rm -rf ssfi
	rm -rf build/* 
