CC = /usr/bin/clang++
CFLAGS = --std=c++11 -Wall -Wextra
LDFLAGS = -pthread -lboost_system -lboost_filesystem -lboost_program_options -lboost_thread -lboost_log
INCLUDE = -I/usr/include/boost
DFLAGS = -DBOOST_LOG_DYN_LINK

all: src/main.cpp worker_queue.o boost_asio_queue.o file_locator.o parser.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(DFLAGS) src/main.cpp build/parser.o build/worker_queue.o build/boost_asio_queue.o build/file_locator.o -o ssfi

worker_queue.o: src/worker_queue.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(DFLAGS) -c src/worker_queue.cpp -o build/worker_queue.o

boost_asio_queue.o: src/boost_asio_queue.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(DFLAGS) -c src/boost_asio_queue.cpp -o build/boost_asio_queue.o

file_locator.o: src/file_locator.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(DFLAGS) -c src/file_locator.cpp -o build/file_locator.o

parser.o: src/parser.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(DFLAGS) -c src/parser.cpp -o build/parser.o

clean:
	rm -rf ssfi
	rm -rf build/* 
