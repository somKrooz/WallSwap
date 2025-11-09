CC = gcc
CFLAGS = -I include
SRCS = main.c Ini.c utility.c
TARGET = wall

all:
	$(CC) $(SRCS) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
