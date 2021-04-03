CC = g++
CFLAGS = -std=c++17 -MMD

BIN_DIR    = ./bin
BUILD_DIR  = ./build
SRC_DIR    = ./src
TESTS_DIR  = ./tests

MAIN_FILE  = main.cpp

OUTS_MAIN      = $(BIN_DIR)/main
OUTS_MAIN_TEST = $(BIN_DIR)/main_test


SRCS      := $(filter-out $(SRC_DIR)/main.cpp, \
             $(wildcard $(SRC_DIR)/*.cpp))
SRCS_TEST := $(filter-out $(TESTS_DIR)/main.cpp, \
             $(wildcard $(TESTS_DIR)/*.cpp))

OBJECT_SRCS      := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJECT_SRCS_TEST := $(SRCS_TEST:$(TESTS_DIR)/%.cpp=$(BUILD_DIR)/%.o)

DEPENDENCIES := $(OBJECT_SRCS:.o=.d)
TEST_DEPENDENCIES := $(OBJECT_SRCS:.o=.d)

$(OUTS_MAIN): $(OBJECT_SRCS) $(BUILD_DIR)/main.o
	@echo "LINKING OBJECTS TO EXECUTABLE $(OUTS_MAIN)"
	$(CC) $(CFLAGS) $^ -o $(OUTS_MAIN)
	@echo "Done."

$(OUTS_MAIN_TEST): $(OBJECT_SRCS) $(OBJECT_SRCS_TEST) $(BUILD_DIR)/tmain.o
	@echo "LINKING OBJECTS TO EXECUTABLE $(OUTS_MAIN_TEST)"
	$(CC) $(CFLAGS) $^ -o $(OUTS_MAIN_TEST)
	@echo "Done."

$(BUILD_DIR)/%_test.o: $(TESTS_DIR)/%_test.cpp
	@echo "BUILDING CHANGED TEST OBJECT $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/tmain.o: $(TESTS_DIR)/$(MAIN_FILE)
	@echo "BUILDING CHANGED TMAIN $@"
	 $(CC) $(CFLAGS) -c $^ -o ./build/tmain.o

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "BUILDING CHANGED OBJECT $@"
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPENDENCIES) $(TEST_DEPENDENCIES)

clean:
	@rm -rf $(BUILD_DIR)/* $(BIN_DIR)/* 

