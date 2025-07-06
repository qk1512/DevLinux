CC = gcc
CFLAGS = -Wall -g
BUILD_DIR = build
TARGET = $(BUILD_DIR)/filestat

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): filestat.c
	$(CC) $(CFLAGS) filestat.c -o $(TARGET)

clean:
	rm -rf $(BUILD_DIR)