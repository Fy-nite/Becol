VERSION := 1.0.0
LIB_VERSION := 1.0.0
NAME := becol

CXX     := gcc
TARGET = bin/$(NAME)
LIB_TARGET = bin/lib$(NAME).so
WIN_TARGET = bin/$(NAME).exe
WIN_LIB_TARGET = bin/lib$(NAME).dll
LIBS = -lm
CC ?= gcc
CFLAGS = -g -Wall -DCOMMIT="\"$(shell git describe --always --dirty)\"" -DVERSION="\"$(VERSION)\"" -DSOURCE="\"$(shell git remote get-url $(shell git remote))\"" -Werror
LIB_CFLAGS = -fPIC -DVERSION="\"$(LIB_VERSION)\""

.PHONY: default all clean

default: release
release: $(TARGET)
debug: CFLAGS += -g -fsanitize=address
debug: $(TARGET)
all: default

windows: CC = x86_64-w64-mingw32-gcc
windows: TARGET = $(WIN_TARGET)
windows: LIB_TARGET = $(WIN_LIB_TARGET)
windows: $(WIN_TARGET)

OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c))
LIB_OBJECTS = $(patsubst %.c, %.o, $(shell find src/lib$(NAME) -name "*.c"))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(WIN_TARGET) $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS) $(LIB_TARGET)
	mkdir bin -p
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@ -L. -l:$(LIB_TARGET) $(CFLAGS)

$(LIB_TARGET): CFLAGS += $(LIB_CFLAGS)
$(LIB_TARGET): $(LIB_OBJECTS)
	mkdir bin -p
	$(CC) $(LIB_OBJECTS) -Wall -Werror -shared $(LIBS) -o $@ $(CFLAGS)

$(WIN_TARGET): $(OBJECTS) $(WIN_LIB_TARGET)
	mkdir bin -p
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@ -L. -l:$(LIB_TARGET)

$(WIN_LIB_TARGET): CFLAGS += $(LIB_CFLAGS)
$(WIN_LIB_TARGET): $(LIB_OBJECTS)
	mkdir bin -p
	$(CC) $(LIB_OBJECTS) -Wall -Werror -shared $(LIBS) -o $@

clean:
	-find . -name *.o -delete
	-rm -rf bin/*

run: $(TARGET)
	$(TARGET)
