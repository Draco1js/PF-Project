CC = gcc
CFLAGS = -Wall -Iinclude
TARGET = hotel
SOURCES = src/main.c src/guest.c src/admin.c src/room.c src/services.c src/database.c src/error_handling.c
OBJECTS = $(patsubst src/%.c,build/%.o,$(SOURCES))

all: $(TARGET) run

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build $(TARGET)