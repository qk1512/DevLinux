# Makefile

CC = gcc
CFLAGS = -Wall -Iheader_file
OBJDIR = build
SRCDIR = c_file

# File nguồn
MAIN_SRC = main.c
MODULE_SRCS = $(wildcard $(SRCDIR)/*.c)
ALL_SRCS = $(MAIN_SRC) $(MODULE_SRCS)

# Tạo danh sách file .o trong build/
MAIN_OBJ = $(OBJDIR)/main.o
MODULE_OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(MODULE_SRCS))
ALL_OBJS = $(MAIN_OBJ) $(MODULE_OBJS)

TARGET = main

# Quy tắc mặc định
all: $(TARGET)

# Link các object thành file thực thi
$(TARGET): $(ALL_OBJS)
	$(CC) -o $@ $^

# Biên dịch main.c
$(OBJDIR)/main.o: main.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Biên dịch các file .c trong c_file/
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Dọn sạch
clean:
	rm -rf $(OBJDIR) $(TARGET)
