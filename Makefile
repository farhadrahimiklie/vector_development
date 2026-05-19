.SILENT:

CC      = gcc
CSTD    = c18
TARGET  = main

# -fsanitize=address,undefined -O0 \

CFLAGS  = -g -Wall -Wextra -Wpedantic -Werror \
		  -std=$(CSTD) -fstack-protector-strong \
		  -fno-omit-frame-pointer -march=native

SRC     = $(wildcard *.c)
OBJ     = $(SRC:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)
	rm -f $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET)
