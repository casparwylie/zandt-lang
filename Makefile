CC = g++
CFLAGS = -std=c++11

BIN_DIR    = ./bin
BUILD_DIR  = ./build
SRC_DIR    = ./src
TESTS_DIR  = ./tests

OUTS_MAIN      = $(BIN_DIR)/main
OUTS_MAIN_TEST = $(BIN_DIR)/main_test

SRCS       = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS    = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

main: $(OBJECTS)
	@echo "LINKING OBJECTS TO EXECUTABLE $(OUTS_MAIN)"
	$(CC) $(CFLAGS) $^ -o $(OUTS_MAIN)
	@echo "Done."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "BUILDING CHANGED OBJECT $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)/* $(BIN_DIR)/* 

