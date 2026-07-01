CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

TARGET = ttt
SRC = src/ttt.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.exe *.out
