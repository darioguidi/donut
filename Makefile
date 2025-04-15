CC = gcc
CFLAGS = -Wall
LIBS = -lX11 -lm

TARGET = donut
SRC = donut.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
