CC = g++
CFLAGS = -std=c++17

BIN_DIR    = ./bin
BUILD_DIR  = ./build
SRC_DIR    = ./src
TESTS_DIR  = ./tests

OUTS_MAIN      = $(BIN_DIR)/main
OUTS_MAIN_TEST = $(BIN_DIR)/main_test


SRCS      := $(filter-out $(SRC_DIR)/main.cpp, \
             $(wildcard $(SRC_DIR)/*.cpp))
SRCS_TEST := $(filter-out $(TESTS_DIR)/main.cpp, \
             $(wildcard $(TESTS_DIR)/*.cpp))

OBJECT_SRCS      := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJECT_SRCS_TEST := $(SRCS_TEST:$(TESTS_DIR)/%.cpp=$(BUILD_DIR)/%.o)

$(OUTS_MAIN): $(OBJECT_SRCS)
	@echo "LINKING OBJECTS TO EXECUTABLE $(OUTS_MAIN)"
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) $^ $(BUILD_DIR)/main.o -o $(OUTS_MAIN)
	@echo "Done."

$(OUTS_MAIN_TEST): $(OBJECT_SRCS) $(OBJECT_SRCS_TEST)
	@echo "LINKING OBJECTS TO EXECUTABLE $(OUTS_MAIN_TEST)"
	$(CC) $(CFLAGS) -c $(TESTS_DIR)/main.cpp -o $(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) $^ $(BUILD_DIR)/main.o -o $(OUTS_MAIN_TEST)
	@echo "Done."

$(BUILD_DIR)/%_test.o: $(TESTS_DIR)/%_test.cpp
	@echo "BUILDING CHANGED TEST OBJECT $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "BUILDING CHANGED OBJECT $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)/* $(BIN_DIR)/* 

