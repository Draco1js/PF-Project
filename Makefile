CC = gcc
CFLAGS = -Wall
TARGET = hotel
SOURCES = main.c guest.c admin.c room.c services.c database.c error_handling.c
OBJECTS = $(patsubst %.c,build/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

build/%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)
