CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
INCLUDES = -I./common \
           -I./src/data-structures/linear-queue \
           -I./src/data-structures/circular-queue \
           -I./src/data-structures/doubly-linked-list \
           -I./src/data-structures/binary-search-tree \
           -I./src/data-structures/hash-table

SRC = src/main.c \
      src/data-structures/linear-queue/linear_queue.c \
      src/data-structures/circular-queue/circular_queue.c \
      src/data-structures/doubly-linked-list/playlist.c \
      src/data-structures/binary-search-tree/genre_bst.c \
      src/data-structures/hash-table/hash_table.c

TARGET = music_system

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) *.o *.dSYM
