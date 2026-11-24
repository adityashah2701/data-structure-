CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
INCLUDES = -I./common -I./src/data-structures/linear-queue -I./src/data-structures/circular-queue

SRC = src/main.c \
      src/data-structures/linear-queue/linear_queue.c \
      src/data-structures/circular-queue/circular_queue.c

TARGET = music_system

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) *.o *.dSYM
