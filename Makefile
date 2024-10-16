CC = gcc
CFLAGS = -Wall -Iinclude
TARGET = hotel
TEST_TARGET = test_hotel
SOURCES = src/main.c src/guest.c src/admin.c src/database.c src/error_handling.c
OBJECTS = $(patsubst src/%.c,build/%.o,$(SOURCES))
TEST_SOURCES = tests/test.c
TEST_OBJECTS = $(patsubst tests/%.c,build/%.o,$(TEST_SOURCES))

all: $(TARGET) run

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: tests/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS)

clean:
	rm -rf build $(TARGET) $(TEST_TARGET)