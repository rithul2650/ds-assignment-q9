CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
SRC = src/main.c src/k_way_merge.c src/pairwise_merge.c
TARGET = k_way_merge_app

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.exe src/*.o

run: all
	./$(TARGET)
