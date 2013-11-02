CC = gcc
TARGET_DIR = bin

SRC_DIR = src
BUILD_DIR = build

TEST_DIR = test
TEST_BUILD_DIR = build/test
TEST_INC = -I test/include


SRC_EXT = c
SOURCES = $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJECTS = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.o))

CFLAGS = -g -Wall
INC = -I include

.PHONY: all
all: $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.$(SRC_EXT)
	mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) $(TEST_INC) -c -o $@ $<

$(TARGET_DIR)/%: $(OBJECTS) $(TEST_BUILD_DIR)/%.o
	mkdir -p $(TARGET_DIR)
	$(CC) $^ -o $@

.PHONY : clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET_DIR)
