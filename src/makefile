# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17 -I../libs

# Source files and headers
SRCS = main.cpp preprocess.cpp
HEADERS = activation.hpp layer.hpp network.hpp preprocess.hpp
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = main.out

# Default rule
all: $(TARGET)

# Linking the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compiling source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
