# Compilatore
CC = gcc

CFLAGS = -Wall -std=c99

# Librerie
LIBS = -lSDL2 -lm

TARGET = donut
SRC = donut.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
