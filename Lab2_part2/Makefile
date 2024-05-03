CC=g++
CFLAGS=-std=c++17 -Wall -g


# The source files we use for building custom_tests
ALL_SRC=$(wildcard *.cpp)

# The name of the resulting executable
APP=Mihir

custom_tests:
	$(CC) $(CFLAGS) unittestmain.cpp main.cpp -o $(APP)	
	./$(APP)

clean:
	rm -f $(APP)
