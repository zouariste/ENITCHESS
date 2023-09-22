# Specify the C++ compiler and compiler flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11

# Specify the name of the target executable
TARGET := EnitChess

# Specify the directories for SFML includes and libraries
SFML_INCLUDE := /usr/include
SFML_LIB := /usr/lib

# Specify the SFML libraries to link
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Default target
all: $(TARGET)

# Use the find command to locate all source files
SRCS := $(shell find . -type f -name '*.cpp')

# Generate a list of object files from source files
OBJS := $(SRCS:.cpp=.o)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ -L$(SFML_LIB) $(SFML_LIBS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(SFML_INCLUDE) -c $< -o $@

# Rule to install SFML (if not already installed)
install_sfml:
	sudo apt-get install libsfml-dev

# Clean the project directory
clean:
	rm -f $(OBJS) $(TARGET)

# Phony target to force "install_sfml" to always run
.PHONY: install_sfml

# Phony target to clean the project
.PHONY: clean
