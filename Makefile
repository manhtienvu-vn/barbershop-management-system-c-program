# 1. Khai báo Trình biên dịch và Cờ (Flags)
CC = gcc
CFLAGS = -w -g

# 2. Danh sách các file nguồn (.c)
SRCS = main.c operation.c logic.c ui.c fileio.c

# 3. Tự động chuyển tên .c thành .o (Object files)
OBJS = $(SRCS:.c=.o)

# 4. Tên file thực thi đầu ra (Output)
TARGET = app.exe

# --- CÁC LỆNH (RULES) ---

all: $(TARGET)

# Lệnh liên kết các file .o thành file .exe cuối cùng
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Lệnh biên dịch từng file .c thành file .o
# $< là file nguồn, $@ là file đích
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /f $(OBJS) $(TARGET)