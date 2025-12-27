.PHONY: all clean

CC=g++
CXXFLAGS=-std=c++17 -Wall -Werror -Wextra
INCLUDE=-Iinclude
EXECUTABLE=lab-07_matrix

SRCS=$(wildcard src/*.cpp)
INCS=$(wildcard include/*.h)
OBJS=$(patsubst src/%.cpp,obj/%.o,$(SRCS))

all: $(EXECUTABLE)

obj:
	mkdir obj

obj/%.o: src/%.cpp $(INCS) | obj
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)

clear:
	rm -rf obj
	rm $(EXECUTABLE)