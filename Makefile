# Compilatore
CC = gcc

CFLAGS = -Wall

# Librerie
LIBS = -lX11 -lm


TARGET = donut

# Alias del eseguibile
SRC = donut.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
