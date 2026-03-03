CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g
CLIBS = -lSDL2
CSRCS := $(wildcard src/*.c)
TARGET = alpha_tac
BUILD_DIR = build

$(BUILD_DIR)/$(TARGET): $(C_SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(CSRCS) $(CLIBS)

clean:
	rm -r $(BUILD_DIR)
