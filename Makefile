CXX=g++
CXXFLAGS=-Wall -std=c++20 -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -Wpedantic -Wconversion -fstack-protector-all -fsanitize=address -fsanitize=undefined
INCLUDES=-I./src/headers
SRC=$(wildcard ./src/*.cpp)
OBJ=$(SRC:.cpp=.o)
TARGET=ipk-sniffer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(SRC:.cpp=.o) $(TARGET)