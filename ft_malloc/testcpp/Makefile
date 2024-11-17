
TARGET = main

SRC_DIR = .
OBJ_DIR = ./obj
LIB_DIR = ..

SRC = $(SRC_DIR)/main.cpp

OBJ = $(OBJ_DIR)/main.o

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g -ldl

MKDIR_P = mkdir -p

all: $(TARGET)

$(TARGET): $(OBJ) 
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR_P) $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

val:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)


.PHONY: all clean fclean re
