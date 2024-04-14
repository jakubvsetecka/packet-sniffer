CXX=g++
CXXFLAGS=-Wall -std=c++20 -g -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -Wpedantic -Wconversion -fstack-protector-all -fsanitize=address -fsanitize=undefined
INCLUDES=-I./src/header
LIBS=-lpcap
SRC=$(wildcard ./src/*.cpp)
OBJ=$(SRC:.cpp=.o)
DEPS=$(OBJ:.o=.d)  # Dependency files for header changes
TARGET=ipk-sniffer

all: $(TARGET)

# Include dependency files if they exist
-include $(DEPS)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

pack:
	zip -r xvsete00.zip src/ Makefile README.md CHANGELOG.md

clean:
	rm -f $(OBJ) $(DEPS) $(TARGET) xvsete00.zip

.PHONY: all pack clean
