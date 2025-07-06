CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -Lstatic -Lshared
BUILD_DIR = build
STATIC_DIR = static
SHARED_DIR = shared

all: $(BUILD_DIR) $(STATIC_DIR) $(SHARED_DIR) main_static main_shared

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(STATIC_DIR):
	mkdir -p $(STATIC_DIR)

$(SHARED_DIR):
	mkdir -p $(SHARED_DIR)

# Static library
$(STATIC_DIR)/libstrutils.a: $(BUILD_DIR)/strutils.o
	ar rcs $(STATIC_DIR)/libstrutils.a $(BUILD_DIR)/strutils.o

$(BUILD_DIR)/strutils.o: strutils.c strutils.h
	$(CC) $(CFLAGS) -c strutils.c -o $(BUILD_DIR)/strutils.o

main_static: $(BUILD_DIR)/main.o $(STATIC_DIR)/libstrutils.a
	$(CC) $(BUILD_DIR)/main.o $(LDFLAGS) -lstrutils -o $(BUILD_DIR)/main_static

# Shared library
$(SHARED_DIR)/libstrutils.so: strutils.c strutils.h
	$(CC) $(CFLAGS) -fPIC -shared strutils.c -o $(SHARED_DIR)/libstrutils.so

main_shared: $(BUILD_DIR)/main.o $(SHARED_DIR)/libstrutils.so
	$(CC) $(BUILD_DIR)/main.o $(LDFLAGS) -lstrutils -o $(BUILD_DIR)/main_shared

$(BUILD_DIR)/main.o: main.c strutils.h
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR) $(STATIC_DIR) $(SHARED_DIR)