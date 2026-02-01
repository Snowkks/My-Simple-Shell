CC = gcc

TARGET = myshell

SRC = myshell.c

all:
	$(CC) $(SRC) -o $(TARGET)
	@echo "Build successful! Run with: sudo ./$(TARGET)"

clean:
	rm -f $(TARGET)
