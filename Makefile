CXX=clang++
CC=clang
CPP_FLAGS=-Wall -Wextra -std=c++17
LD_FLAGS=
LD_LIBS=-lcurl

BUILD_DIR=./build/
SRC_DIR=
SRCS:=main.cpp query.cpp parse.cpp
OBJS:=$(BUILD_DIR)$(SRCS:.cpp=.o)
TARGET:=$(BUILD_DIR)tkl

$(TARGET): $(OBJS)
	$(CXX) $(LD_LIBS) $^ -o $@ 

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CPP_FLAGS) -c $< -o $@

$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CPP_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR) 
