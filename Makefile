NAME=llgml

SDL_IDIR="C:\Program Files (x86)\SDL2\include"
SDL_LDIR="C:\Program Files (x86)\SDL2\lib"

INCLUDE_DIR=include
SRC_DIR=src
CC=gcc
CFLAGS=-Wall -Werror -Wno-unused -std=gnu2x -I$(INCLUDE_DIR) -lm
ifeq ($(OS),Windows_NT)
	BUILD_DIR=buildNT
	LIB_SUFFIX=lib
	MKLIB=$(CC) -static -o
	CFLAGS += -lmingw32 -I$(SDL_IDIR) -L$(SDL_LDIR)
else
	BUILD_DIR=build
	LIB_SUFFIX=a
	MKLIB=ar rcs
endif
CFLAGS += -lSDL2main -lSDL2


INCLUDES=$(wildcard $(INCLUDE_DIR)/*.h)
SRCS=$(wildcard $(SRC_DIR)/*.c)
_=$(SRCS:%.c=%.o)
OBJS=$(_:$(SRC_DIR)%=$(BUILD_DIR)%)

$(BUILD_DIR)/$(NAME): $(OBJS) | $(BUILD_DIR)
	$(MKLIB) $@.$(LIB_SUFFIX) $^

$(OBJS): $(SRCS) $(INCLUDES) | $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) | $(BUILD_DIR)
	$(CC) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)


.PHONY: clean test

clean:
	$(RM) -r $(BUILD_DIR)

TEST_DIR=test
TEST_SRCS=$(wildcard $(TEST_DIR)/*.c)
test: $(BUILD_DIR)/$(NAME)
	$(CC) -o $(BUILD_DIR)/$@ $(TEST_SRCS) -I$(INCLUDE_DIR) -L$(BUILD_DIR) $(CFLAGS)