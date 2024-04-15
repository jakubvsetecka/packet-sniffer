CXX=g++
CXXFLAGS=-Wall -std=c++20 -g -Wextra #-Wshadow -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual -Wpedantic -Wconversion -fstack-protector-all -fsanitize=address -fsanitize=undefined
INCLUDES=-I./src/header -I/usr/include/gtest/ -I/usr/include/gmock/
LIBS=-lpcap -lgtest -lgtest_main -lgmock -lpthread
SRC=$(wildcard ./src/*.cpp)
OBJ=$(SRC:.cpp=.o)
DEPS=$(OBJ:.o=.d)  # Dependency files for header changes
TARGET=ipk-sniffer
TEST_SRC=$(wildcard ./src/*_test.cpp)
TEST_OBJ=$(TEST_SRC:.cpp=.o)
TEST_TARGET=run_tests

all: $(TARGET)

# Include dependency files if they exist
-include $(DEPS)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST_OBJ) $(LIBS) -o $@
	./$(TEST_TARGET)

pack:
	zip -r xvsete00.zip src/ Makefile README.md CHANGELOG.md

clean:
	rm -f $(OBJ) $(DEPS) $(TARGET) $(TEST_OBJ) $(TEST_TARGET) xvsete00.zip

.PHONY: all test pack clean
