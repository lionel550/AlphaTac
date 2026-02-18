CC = gcc
CFLAGS = -I include -Wall -Wextra -Wpedantic -g
TARGET = alpha_tac
BUILD_DIR = build
C_SRCS := $(wildcard src/*.c)

$(BUILD_DIR)/$(TARGET): $(C_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(C_SRCS)

clean:
	rm -r $(BUILD_DIR)
