CC = gcc
SRC_DIR = src
BUILD_DIR = build

SRC_EXT = c
SOURCES = $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJECTS = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.o))

CFLAGS = -g -Wall
INC = -I include

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

.PHONY : clean
clean:
	rm -r $(BUILD_DIR)
