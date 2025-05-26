CC = gcc

CFLAGS = -Wall -std=c99

# Librerie (aggiunto -lmingw32 e -lSDL2main)
LIBS = -lmingw32 -lSDL2main -lSDL2 -lm

TARGET = donut
SRC = donut.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

