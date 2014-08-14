CC = /usr/bin/clang++
CFLAGS = --std=c++11 -Wall -Wextra
LDFLAGS = -pthread -lboost_system -lboost_filesystem -lboost_program_options -lboost_thread -lboost_log -lboost_regex
INCLUDE = -I/usr/include/boost -Isrc
DFLAGS = -DBOOST_LOG_DYN_LINK -DSOLIDFIRE_TESTING

all: ssfi test_file_locator test_parser

ssfi: src/main.cpp worker_queue.o boost_asio_queue.o file_locator.o parser.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $(DFLAGS) src/main.cpp build/parser.o build/worker_queue.o build/boost_asio_queue.o build/file_locator.o -o ssfi

test_file_locator: unit_test/test_file_locator.cpp worker_queue.o boost_asio_queue.o file_locator.o parser.o
	$(CC) $(CFLAGS) $(INCLUDE) $(DFLAGS) $(LDFLAGS) unit_test/test_file_locator.cpp build/parser.o build/worker_queue.o build/file_locator.o -o test_file_locator

test_parser: unit_test/test_parser.cpp worker_queue.o boost_asio_queue.o file_locator.o parser.o
	$(CC) $(CFLAGS) $(INCLUDE) $(DFLAGS) $(LDFLAGS) unit_test/test_parser.cpp build/parser.o build/worker_queue.o build/file_locator.o -o test_parser

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
	rm -rf test_file_locator
	rm -rf test_parser
	rm -rf build/*
